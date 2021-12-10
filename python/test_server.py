#!/usr/bin/env python3
# asyncq.py

import asyncio
import itertools as it
import os
import random
import time
import socket
import typing


def log(who, what):
    who = f"{who}:"
    print(f"{who:<10s} {what}")


async def makeitem(size: int = 5) -> str:
    return os.urandom(size).hex()


async def randsleep(caller=None) -> None:
    i = random.randint(5, 15)
    if caller:
        print(f"{caller} sleeping for {i} seconds.")
    await asyncio.sleep(i)


async def produce(name: int, q: asyncio.Queue) -> None:
    n = random.randint(0, 10)
    for _ in it.repeat(None, n):  # Synchronous loop for each single producer
        await randsleep(caller=f"Producer {name}")
        i = await makeitem()
        t = time.perf_counter()
        await q.put((i, t))
        print(f"Producer {name} added <{i}> to queue.")


async def consume(name: int, q: asyncio.Queue) -> None:
    while True:
        await randsleep(caller=f"Consumer {name}")
        i, t = await q.get()
        now = time.perf_counter()
        print(f"Consumer {name} got element <{i}>"
              f" in {now-t:0.5f} seconds.")
        q.task_done()


async def ticks() -> None:
    while True:
        await asyncio.sleep(5)
        log("ticks", "Tick!")



async def sock_handle_input(reader, writer) -> None:
    log("sock", f"callback called, {reader!r}")
    while True:
        data = await reader.readline()
        message = data.decode()
        addr = writer.get_extra_info('peername')

        m = message.rstrip("\n")
        msg = f"received message '{m}'"
        log("sock", msg)
        writer.write((msg + "\n").encode("utf-8"))
        await writer.drain()


async def sock_server() -> None:
    log("sock", "starting server")
    server = await asyncio.start_unix_server(sock_handle_input,
                                             path="/tmp/test_server.sock")
    log("sock", "server started")
    async with server:
        await server.serve_forever()


async def sock_handle_tcp_input(reader, writer) -> None:
    log("tcp", f"callback called, {reader!r}")
    while True:
        data = await reader.readline()
        message = data.decode()
        addr = writer.get_extra_info('peername')

        m = message.rstrip("\n")
        msg = f"received message '{m}' from {addr!r}"
        log("tcp", msg)
        writer.write((msg + "\n").encode("utf-8"))
        await writer.drain()


async def tcp_server() -> None:
    log("tcp", "starting server")

    # asyncio disables dual stack, so create our own dual stack socket.
    sock = socket.socket(socket.AF_INET6, socket.SOCK_STREAM)
    sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    sock.bind(('::', 8889))
    
    server = await asyncio.start_server(sock_handle_tcp_input, sock=sock)
    log("tcp", "server started")
    async with server:
        await server.serve_forever()


async def main(nprod: int, ncon: int):
    q = asyncio.Queue()
    producers = [asyncio.create_task(produce(n, q)) for n in range(nprod)]
    consumers = [asyncio.create_task(consume(n, q)) for n in range(ncon)]

    servers = []
    servers.append(asyncio.create_task(ticks()))
    servers.append(asyncio.create_task(sock_server()))
    servers.append(asyncio.create_task(tcp_server()))

    await asyncio.gather(*producers, *servers, return_exceptions=True)
    await q.join()  # Implicitly awaits consumers, too
    for c in consumers:
        c.cancel()


if __name__ == "__main__":
    import argparse
    random.seed(444)
    parser = argparse.ArgumentParser()
    parser.add_argument("-p", "--nprod", type=int, default=1)
    parser.add_argument("-c", "--ncon", type=int, default=5)
    ns = parser.parse_args()
    start = time.perf_counter()
    asyncio.run(main(**ns.__dict__))
    elapsed = time.perf_counter() - start
    print(f"Program completed in {elapsed:0.5f} seconds.")

