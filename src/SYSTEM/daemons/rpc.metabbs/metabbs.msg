LEVEL2 {}

 The telnet port you're using to allow connections to the
 system should be entered here. This will be used to both
 advertise the system and originate connections.

 To disable MetaBBS access to your system, set the port to
 0. There's actually another way to do this: set the ALLOW
 setting to something imaginary, like noname.noname.noname.
 In either case, the system won't be visible on other
 systems' MetaBBS clients.

TELPRT {Telnet port used for this system (0=disable MetaBBS): 9999} N 0 65535


 If your system has a WWW page devoted to it, this should
 contain the URL.

URL {} S 128 URL of BBS's webpage (if any):



 This is the email address that will be advertised to other
 systems. It should be the Sysop's address, or the address
 of someone willing to answer questions and process requests.

EMAIL {} S 80 Official BBS (or Sysop's) Email address



 This is a list of all the other MetaBBS-aware BBSs you'll allow telnet
 access from.  This does not apply to individual people using their own
 telnet clients from home, but entire systems that might allow their users
 to connect to you through the MetaBBS client. Entire systems providing a
 telnet access to this system will not be stopped, either. For a more
 restrictive and generic access list, have a look at the TCP wrapper,
 tcpd, and its access list files, /etc/hosts.allow and /etc/hosts.deny.

 The access list is a space-delimited list of Internet host addresses (eg
 10.159.34.3 or bbs.soup.com), or BBS addresses (each host may run more than
 one BBS, that's why we need MetaBBS in the first place). BBS addresses are
 host addresses followed by a slash and a BBS codename (e.g
 10.159.34.3/CRAZY or vennea.demon.co.uk/MEGISTOS).
 For a BBS to connect, it must pass both the ALLOW and DENY filters.

 Leave this field empty if you wish to allow *everyone* access.


ALLOW {} S 256 MetaBBS clients allowed to connect


 This is a list of MetaBBS-aware BBSs you do NOT want to allow telnet
 access from.  This does not apply to individual people using their own
 telnet clients from home, but entire systems that might allow their users
 to connect to you through the MetaBBS client. Entire systems providing a
 telnet access to this system will not be stopped, either. For a more
 restrictive and generic access list, have a look at the TCP wrapper,
 tcpd, and its access list files, /etc/hosts.allow and /etc/hosts.deny.

 The access list is a space-delimited list of Internet host addresses (eg
 10.159.34.3 or bbs.soup.com), or BBS addresses (each host may run more than
 one BBS, that's why we need MetaBBS in the first place). BBS addresses are
 host addresses followed by a slash and a BBS codename (e.g
 10.159.34.3/CRAZY or vennea.demon.co.uk/MEGISTOS).
 For a BBS to connect, it must pass both the ALLOW and DENY filters.

 Leave this field empty if you don't want to disallow access to anyone.


DENY {} S 256 MetaBBS clients expressly denied connections


 The 'information package' MetaBBS sends to other interested systems
 contains an optional ASCII art ad of the system. Only the first 8192 bytes
 will be transmitted, to save bandwidth.  The ad is presented to users who
 expressly request more info on your BBS before connecting. List good points
 and keep it short and sweet.


BBSAD {
[0;1;30m[37C[0;1mл[0mлллл
[36C[1mллл[0mлллл
[35C[1mллллл[0mлллл
[34C[1mллллллл[0mлллл
[33C[1mлллл[30mл[37mлллл[0mлллл
[32C[1mлллл[30mллл[37mлллл[0mлллл
[31C[1mлллл[30mлллл [37mлллл[0mлллл
[30C[1mлллл[30mлллл   [37mлллл[0mлллл
[29C[1mлллл[30mлллл[5C[37mлллл[0mлллл
[28C[1mлллл[30mлллл[7C[37mлллл[0mлллл
[27C[1mлллл[30mлллл[9C[37mлллл[0mлллл
[26C[1mлллл[30mлллл[11C[37mлллл[0mлллл
[25C[1mлллл[30mлллл[13C[37mлллл[0mлллл
[24C[1mлллл[30mлллл[15C[37mлллл[0mлллл
[23C[1mлллл[30mлллл[0mллллллллллллллллллллллллл
[22C[1mлллл[30mлллл[0mллллллллллллллллллллллллллл
[22C[1mллл[30mлллллллллллллллллллллллллллллллл
[23C[37mл[30mлллллллллллллллллллллллллллллллл

[24C[37mP R O J E C T   M E G I S T O S

THIS IS AN EXPERIMENTAL BBS -- PLEASE IGNORE THIS.
} T MetaBBS ad of the system (only the first 8192 bytes are used)












 Apart from our own, local Megistos-based BBSs, we can register additional
 local or remote systems that aren't running Megistos (eg Unix shell hosts,
 MUDs, etc). This is done by filling in the required information in this and
 the next fields. This field is the codename of the remote system. It's only
 used in the MetaBBS client. Make it descriptive. If not specified, this
 system won't be registered at all.

SYS1COD {} S 8 Non-Megistos System #1: codename (empty=disable System #1)

 This is a longer, descriptive title for System #1. Include the hostname if
 you can, so that users will know where they're about to connect in case
 they want to do it on their own, without tying up one of our lines.

SYS1TTL {} S 51 Non-Megistos System #1: title

 Optional company name of the remote system.

SYS1CMP {} S 47 Non-Megistos System #1: company

 Optional address of the remote system (line 1 of 2).

SYS1AD1 {} S 47 Non-Megistos System #1: address (line 1)

 Optional address of the remote system (line 2 of 2).

SYS1AD2 {} S 47 Non-Megistos System #1: address (line 2)

 City the remote system lives in. Optional.

SYS1CTY {} S 47 Non-Megistos System #1: city

 A voice contact number. Optional.

SYS1VPH {} S 47 Non-Megistos System #1: voice phone number

 A data number for direct connections, if this is a BBS or an ISP.

SYS1DPH {} S 47 Non-Megistos System #1: data phone number

 The hostname of the remote system. Obligatory: if you leave this
 out, System #1 will not be registered since we won't know where to
 connect to. The address is either in dotted quad form, or a
 fully qualified host and domain name. For example: 10.153.9.27 and
 telnet.bigbbs.com are both acceptable. DNS resolution is be the
 client's responsibility, so be sure the hostname is correct!

SYS1HST {} S 79 Non-Megistos System #1: Internet hostname

 This is the port to which we'll connect. Port 23 is the port
 allocated to the standard telnet service. This is the part after
 the color (:) in a telnet:// url. The default is 23 -- leave it
 there if you don't know a port number.

SYS1PRT {Non-Megistos System #1: Telnet port to use (25=normal telnet): 23} N 0 65535

  The URL of the official web page of the system. Optional.

SYS1URL {} S 128 Non-Megistos System #1: Official web page URL (if any)

  The email address of someone who supports this system. Optional.

SYS1EML {} S 80 Non-Megistos System #1: Support email address (if any)

 The 'information package' MetaBBS sends to other interested systems
 contains an optional ASCII art ad of the system. Only the first 8192 bytes
 will be transmitted, to save bandwidth.  The ad is presented to users who
 expressly request more info on your BBS before connecting. List good points
 and keep it short and sweet. You can leave this empty if you can't be
 bothered to write information on remote systems.

SYS1ADV {} T Non-Megistos System #1: detailed description (<8192 bytes)

 This is a list of all the other MetaBBS-aware BBSs you'll allow telnet
 access from.  This does not apply to individual people using their own
 telnet clients from home, but entire systems that might allow their users
 to connect to you through the MetaBBS client. Entire systems providing a
 telnet access to this system will not be stopped, either. For a more
 restrictive and generic access list, have a look at the TCP wrapper,
 tcpd, and its access list files, /etc/hosts.allow and /etc/hosts.deny.

 The access list is a space-delimited list of Internet host addresses (eg
 10.159.34.3 or bbs.soup.com), or BBS addresses (each host may run more than
 one BBS, that's why we need MetaBBS in the first place). BBS addresses are
 host addresses followed by a slash and a BBS codename (e.g
 10.159.34.3/CRAZY or vennea.demon.co.uk/MEGISTOS).
 For a BBS to connect, it must pass both the ALLOW and DENY filters.

 Leave this field empty if you wish to allow *everyone* access. There's no
 point specifying anything here if this isn't one of your own systems:
 chances are, the remote system will have its own security set up.

SYS1ALW {} S 256 Non-Megistos System #1: hosts/BBSs allowed connections

 This is a list of MetaBBS-aware BBSs you do NOT want to allow telnet
 access from.  This does not apply to individual people using their own
 telnet clients from home, but entire systems that might allow their users
 to connect to you through the MetaBBS client. Entire systems providing a
 telnet access to this system will not be stopped, either. For a more
 restrictive and generic access list, have a look at the TCP wrapper,
 tcpd, and its access list files, /etc/hosts.allow and /etc/hosts.deny.

 The access list is a space-delimited list of Internet host addresses (eg
 10.159.34.3 or bbs.soup.com), or BBS addresses (each host may run more than
 one BBS, that's why we need MetaBBS in the first place). BBS addresses are
 host addresses followed by a slash and a BBS codename (e.g
 10.159.34.3/CRAZY or vennea.demon.co.uk/MEGISTOS).
 For a BBS to connect, it must pass both the ALLOW and DENY filters.

 Leave this field empty if you don't want to disallow access to anyone.
 There's no point specifying anything here if this isn't one of your own
 systems: chances are, the remote system will have its own security set up.

SYS1DNY {} S 256 Non-Megistos System #1: hosts/BBSs denied connections

  Normally, the local line is disconnected after a MetaBBS remote session is
  terminated. Set this to NO if you have *GOOD* reasons to do so (eg the
  Non-Megistos system is often too busy to accept connections, and users are
  annoyed at being disconnected just because of that). Bear in mind that
  this is only a *suggestion* sent to the remote MetaBBS client. It's that
  client that ultimately gets to decide whether to disconnect its users or
  not.

SYS1HUP {Non-Megistos System #1: disconnect line after remote session terminates? YES} B













 Apart from our own, local Megistos-based BBSs, we can register additional
 local or remote systems that aren't running Megistos (eg Unix shell hosts,
 MUDs, etc). This is done by filling in the required information in this and
 the next fields. This field is the codename of the remote system. It's only
 used in the MetaBBS client. Make it descriptive. If not specified, this
 system won't be registered at all.

SYS2COD {} S 8 Non-Megistos System #2: codename (empty=disable System #2)

 This is a longer, descriptive title for System #2. Include the hostname if
 you can, so that users will know where they're about to connect in case
 they want to do it on their own, without tying up one of our lines.

SYS2TTL {} S 51 Non-Megistos System #2: title

 Optional company name of the remote system.

SYS2CMP {} S 47 Non-Megistos System #2: company

 Optional address of the remote system (line 1 of 2).

SYS2AD1 {} S 47 Non-Megistos System #2: address (line 1)

 Optional address of the remote system (line 2 of 2).

SYS2AD2 {} S 47 Non-Megistos System #2: address (line 2)

 City the remote system lives in. Optional.

SYS2CTY {} S 47 Non-Megistos System #2: city

 A voice contact number. Optional.

SYS2VPH {} S 47 Non-Megistos System #2: voice phone number

 A data number for direct connections, if this is a BBS or an ISP.

SYS2DPH {} S 47 Non-Megistos System #2: data phone number

 The hostname of the remote system. Obligatory: if you leave this
 out, System #2 will not be registered since we won't know where to
 connect to. The address is either in dotted quad form, or a
 fully qualified host and domain name. For example: 10.153.9.27 and
 telnet.bigbbs.com are both acceptable. DNS resolution is be the
 client's responsibility, so be sure the hostname is correct!

SYS2HST {} S 79 Non-Megistos System #2: Internet hostname

 This is the port to which we'll connect. Port 23 is the port
 allocated to the standard telnet service. This is the part after
 the color (:) in a telnet:// url. The default is 23 -- leave it
 there if you don't know a port number.

SYS2PRT {Non-Megistos System #2: Telnet port to use (25=normal telnet): 23} N 0 65535

  The URL of the official web page of the system. Optional.

SYS2URL {} S 128 Non-Megistos System #2: Official web page URL (if any)

  The email address of someone who supports this system. Optional.

SYS2EML {} S 80 Non-Megistos System #2: Support email address (if any)

 The 'information package' MetaBBS sends to other interested systems
 contains an optional ASCII art ad of the system. Only the first 8192 bytes
 will be transmitted, to save bandwidth.  The ad is presented to users who
 expressly request more info on your BBS before connecting. List good points
 and keep it short and sweet. You can leave this empty if you can't be
 bothered to write information on remote systems.

SYS2ADV {} T Non-Megistos System #2: detailed description (<8192 bytes)

 This is a list of all the other MetaBBS-aware BBSs you'll allow telnet
 access from.  This does not apply to individual people using their own
 telnet clients from home, but entire systems that might allow their users
 to connect to you through the MetaBBS client. Entire systems providing a
 telnet access to this system will not be stopped, either. For a more
 restrictive and generic access list, have a look at the TCP wrapper,
 tcpd, and its access list files, /etc/hosts.allow and /etc/hosts.deny.

 The access list is a space-delimited list of Internet host addresses (eg
 10.159.34.3 or bbs.soup.com), or BBS addresses (each host may run more than
 one BBS, that's why we need MetaBBS in the first place). BBS addresses are
 host addresses followed by a slash and a BBS codename (e.g
 10.159.34.3/CRAZY or vennea.demon.co.uk/MEGISTOS).
 For a BBS to connect, it must pass both the ALLOW and DENY filters.

 Leave this field empty if you wish to allow *everyone* access. There's no
 point specifying anything here if this isn't one of your own systems:
 chances are, the remote system will have its own security set up.

SYS2ALW {} S 256 Non-Megistos System #2: hosts/BBSs allowed connections

 This is a list of MetaBBS-aware BBSs you do NOT want to allow telnet
 access from.  This does not apply to individual people using their own
 telnet clients from home, but entire systems that might allow their users
 to connect to you through the MetaBBS client. Entire systems providing a
 telnet access to this system will not be stopped, either. For a more
 restrictive and generic access list, have a look at the TCP wrapper,
 tcpd, and its access list files, /etc/hosts.allow and /etc/hosts.deny.

 The access list is a space-delimited list of Internet host addresses (eg
 10.159.34.3 or bbs.soup.com), or BBS addresses (each host may run more than
 one BBS, that's why we need MetaBBS in the first place). BBS addresses are
 host addresses followed by a slash and a BBS codename (e.g
 10.159.34.3/CRAZY or vennea.demon.co.uk/MEGISTOS).
 For a BBS to connect, it must pass both the ALLOW and DENY filters.

 Leave this field empty if you don't want to disallow access to anyone.
 There's no point specifying anything here if this isn't one of your own
 systems: chances are, the remote system will have its own security set up.

SYS2DNY {} S 256 Non-Megistos System #2: hosts/BBSs denied connections

  Normally, the local line is disconnected after a MetaBBS remote session is
  terminated. Set this to NO if you have *GOOD* reasons to do so (eg the
  Non-Megistos system is often too busy to accept connections, and users are
  annoyed at being disconnected just because of that). Bear in mind that
  this is only a *suggestion* sent to the remote MetaBBS client. It's that
  client that ultimately gets to decide whether to disconnect its users or
  not.

SYS2HUP {Non-Megistos System #2: disconnect line after remote session terminates? YES} B












 Apart from our own, local Megistos-based BBSs, we can register additional
 local or remote systems that aren't running Megistos (eg Unix shell hosts,
 MUDs, etc). This is done by filling in the required information in this and
 the next fields. This field is the codename of the remote system. It's only
 used in the MetaBBS client. Make it descriptive. If not specified, this
 system won't be registered at all.

SYS3COD {} S 8 Non-Megistos System #3: codename (empty=disable System #3)

 This is a longer, descriptive title for System #3. Include the hostname if
 you can, so that users will know where they're about to connect in case
 they want to do it on their own, without tying up one of our lines.

SYS3TTL {} S 51 Non-Megistos System #3: title

 Optional company name of the remote system.

SYS3CMP {} S 47 Non-Megistos System #3: company

 Optional address of the remote system (line 1 of 2).

SYS3AD1 {} S 47 Non-Megistos System #3: address (line 1)

 Optional address of the remote system (line 2 of 2).

SYS3AD2 {} S 47 Non-Megistos System #3: address (line 2)

 City the remote system lives in. Optional.

SYS3CTY {} S 47 Non-Megistos System #3: city

 A voice contact number. Optional.

SYS3VPH {} S 47 Non-Megistos System #3: voice phone number

 A data number for direct connections, if this is a BBS or an ISP.

SYS3DPH {} S 47 Non-Megistos System #3: data phone number

 The hostname of the remote system. Obligatory: if you leave this
 out, System #3 will not be registered since we won't know where to
 connect to. The address is either in dotted quad form, or a
 fully qualified host and domain name. For example: 10.153.9.27 and
 telnet.bigbbs.com are both acceptable. DNS resolution is be the
 client's responsibility, so be sure the hostname is correct!

SYS3HST {astarte.bedroomlan} S 79 Non-Megistos System #3: Internet hostname

 This is the port to which we'll connect. Port 23 is the port
 allocated to the standard telnet service. This is the part after
 the color (:) in a telnet:// url. The default is 23 -- leave it
 there if you don't know a port number.

SYS3PRT {Non-Megistos System #3: Telnet port to use (25=normal telnet): 23} N 0 65535

  The URL of the official web page of the system. Optional.

SYS3URL {} S 128 Non-Megistos System #3: Official web page URL (if any)

  The email address of someone who supports this system. Optional.

SYS3EML {} S 80 Non-Megistos System #3: Support email address (if any)

 The 'information package' MetaBBS sends to other interested systems
 contains an optional ASCII art ad of the system. Only the first 8192 bytes
 will be transmitted, to save bandwidth.  The ad is presented to users who
 expressly request more info on your BBS before connecting. List good points
 and keep it short and sweet. You can leave this empty if you can't be
 bothered to write information on remote systems.

SYS3ADV {} T Non-Megistos System #3: detailed description (<8192 bytes)

 This is a list of all the other MetaBBS-aware BBSs you'll allow telnet
 access from.  This does not apply to individual people using their own
 telnet clients from home, but entire systems that might allow their users
 to connect to you through the MetaBBS client. Entire systems providing a
 telnet access to this system will not be stopped, either. For a more
 restrictive and generic access list, have a look at the TCP wrapper,
 tcpd, and its access list files, /etc/hosts.allow and /etc/hosts.deny.

 The access list is a space-delimited list of Internet host addresses (eg
 10.159.34.3 or bbs.soup.com), or BBS addresses (each host may run more than
 one BBS, that's why we need MetaBBS in the first place). BBS addresses are
 host addresses followed by a slash and a BBS codename (e.g
 10.159.34.3/CRAZY or vennea.demon.co.uk/MEGISTOS).
 For a BBS to connect, it must pass both the ALLOW and DENY filters.

 Leave this field empty if you wish to allow *everyone* access. There's no
 point specifying anything here if this isn't one of your own systems:
 chances are, the remote system will have its own security set up.

SYS3ALW {} S 256 Non-Megistos System #3: hosts/BBSs allowed connections

 This is a list of MetaBBS-aware BBSs you do NOT want to allow telnet
 access from.  This does not apply to individual people using their own
 telnet clients from home, but entire systems that might allow their users
 to connect to you through the MetaBBS client. Entire systems providing a
 telnet access to this system will not be stopped, either. For a more
 restrictive and generic access list, have a look at the TCP wrapper,
 tcpd, and its access list files, /etc/hosts.allow and /etc/hosts.deny.

 The access list is a space-delimited list of Internet host addresses (eg
 10.159.34.3 or bbs.soup.com), or BBS addresses (each host may run more than
 one BBS, that's why we need MetaBBS in the first place). BBS addresses are
 host addresses followed by a slash and a BBS codename (e.g
 10.159.34.3/CRAZY or vennea.demon.co.uk/MEGISTOS).
 For a BBS to connect, it must pass both the ALLOW and DENY filters.

 Leave this field empty if you don't want to disallow access to anyone.
 There's no point specifying anything here if this isn't one of your own
 systems: chances are, the remote system will have its own security set up.

SYS3DNY {} S 256 Non-Megistos System #3: hosts/BBSs denied connections

  Normally, the local line is disconnected after a MetaBBS remote session is
  terminated. Set this to NO if you have *GOOD* reasons to do so (eg the
  Non-Megistos system is often too busy to accept connections, and users are
  annoyed at being disconnected just because of that). Bear in mind that
  this is only a *suggestion* sent to the remote MetaBBS client. It's that
  client that ultimately gets to decide whether to disconnect its users or
  not.

SYS3HUP {Non-Megistos System #3: disconnect line after remote session terminates? YES} B












 Apart from our own, local Megistos-based BBSs, we can register additional
 local or remote systems that aren't running Megistos (eg Unix shell hosts,
 MUDs, etc). This is done by filling in the required information in this and
 the next fields. This field is the codename of the remote system. It's only
 used in the MetaBBS client. Make it descriptive. If not specified, this
 system won't be registered at all.

SYS4COD {} S 8 Non-Megistos System #4: codename (empty=disable System #4)

 This is a longer, descriptive title for System #4. Include the hostname if
 you can, so that users will know where they're about to connect in case
 they want to do it on their own, without tying up one of our lines.

SYS4TTL {} S 51 Non-Megistos System #4: title

 Optional company name of the remote system.

SYS4CMP {} S 47 Non-Megistos System #4: company

 Optional address of the remote system (line 1 of 2).

SYS4AD1 {} S 47 Non-Megistos System #4: address (line 1)

 Optional address of the remote system (line 2 of 2).

SYS4AD2 {} S 47 Non-Megistos System #4: address (line 2)

 City the remote system lives in. Optional.

SYS4CTY {} S 47 Non-Megistos System #4: city

 A voice contact number. Optional.

SYS4VPH {} S 47 Non-Megistos System #4: voice phone number

 A data number for direct connections, if this is a BBS or an ISP.

SYS4DPH {} S 47 Non-Megistos System #4: data phone number

 The hostname of the remote system. Obligatory: if you leave this
 out, System #4 will not be registered since we won't know where to
 connect to. The address is either in dotted quad form, or a
 fully qualified host and domain name. For example: 10.153.9.27 and
 telnet.bigbbs.com are both acceptable. DNS resolution is be the
 client's responsibility, so be sure the hostname is correct!

SYS4HST {} S 79 Non-Megistos System #4: Internet hostname

 This is the port to which we'll connect. Port 23 is the port
 allocated to the standard telnet service. This is the part after
 the color (:) in a telnet:// url. The default is 23 -- leave it
 there if you don't know a port number.

SYS4PRT {Non-Megistos System #4: Telnet port to use (25=normal telnet): 23} N 0 65535

  The URL of the official web page of the system. Optional.

SYS4URL {} S 128 Non-Megistos System #4: Official web page URL (if any)

  The email address of someone who supports this system. Optional.

SYS4EML {} S 80 Non-Megistos System #4: Support email address (if any)

 The 'information package' MetaBBS sends to other interested systems
 contains an optional ASCII art ad of the system. Only the first 8192 bytes
 will be transmitted, to save bandwidth.  The ad is presented to users who
 expressly request more info on your BBS before connecting. List good points
 and keep it short and sweet. You can leave this empty if you can't be
 bothered to write information on remote systems.

SYS4ADV {} T Non-Megistos System #4: detailed description (<8192 bytes)

 This is a list of all the other MetaBBS-aware BBSs you'll allow telnet
 access from.  This does not apply to individual people using their own
 telnet clients from home, but entire systems that might allow their users
 to connect to you through the MetaBBS client. Entire systems providing a
 telnet access to this system will not be stopped, either. For a more
 restrictive and generic access list, have a look at the TCP wrapper,
 tcpd, and its access list files, /etc/hosts.allow and /etc/hosts.deny.

 The access list is a space-delimited list of Internet host addresses (eg
 10.159.34.3 or bbs.soup.com), or BBS addresses (each host may run more than
 one BBS, that's why we need MetaBBS in the first place). BBS addresses are
 host addresses followed by a slash and a BBS codename (e.g
 10.159.34.3/CRAZY or vennea.demon.co.uk/MEGISTOS).
 For a BBS to connect, it must pass both the ALLOW and DENY filters.

 Leave this field empty if you wish to allow *everyone* access. There's no
 point specifying anything here if this isn't one of your own systems:
 chances are, the remote system will have its own security set up.

SYS4ALW {} S 256 Non-Megistos System #4: hosts/BBSs allowed connections

 This is a list of MetaBBS-aware BBSs you do NOT want to allow telnet
 access from.  This does not apply to individual people using their own
 telnet clients from home, but entire systems that might allow their users
 to connect to you through the MetaBBS client. Entire systems providing a
 telnet access to this system will not be stopped, either. For a more
 restrictive and generic access list, have a look at the TCP wrapper,
 tcpd, and its access list files, /etc/hosts.allow and /etc/hosts.deny.

 The access list is a space-delimited list of Internet host addresses (eg
 10.159.34.3 or bbs.soup.com), or BBS addresses (each host may run more than
 one BBS, that's why we need MetaBBS in the first place). BBS addresses are
 host addresses followed by a slash and a BBS codename (e.g
 10.159.34.3/CRAZY or vennea.demon.co.uk/MEGISTOS).
 For a BBS to connect, it must pass both the ALLOW and DENY filters.

 Leave this field empty if you don't want to disallow access to anyone.
 There's no point specifying anything here if this isn't one of your own
 systems: chances are, the remote system will have its own security set up.

SYS4DNY {} S 256 Non-Megistos System #4: hosts/BBSs denied connections

  Normally, the local line is disconnected after a MetaBBS remote session is
  terminated. Set this to NO if you have *GOOD* reasons to do so (eg the
  Non-Megistos system is often too busy to accept connections, and users are
  annoyed at being disconnected just because of that). Bear in mind that
  this is only a *suggestion* sent to the remote MetaBBS client. It's that
  client that ultimately gets to decide whether to disconnect its users or
  not.

SYS4HUP {Non-Megistos System #4: disconnect line after remote session terminates? YES} B












 Apart from our own, local Megistos-based BBSs, we can register additional
 local or remote systems that aren't running Megistos (eg Unix shell hosts,
 MUDs, etc). This is done by filling in the required information in this and
 the next fields. This field is the codename of the remote system. It's only
 used in the MetaBBS client. Make it descriptive. If not specified, this
 system won't be registered at all.

SYS5COD {} S 8 Non-Megistos System #5: codename (empty=disable System #5)

 This is a longer, descriptive title for System #5. Include the hostname if
 you can, so that users will know where they're about to connect in case
 they want to do it on their own, without tying up one of our lines.

SYS5TTL {} S 51 Non-Megistos System #5: title

 Optional company name of the remote system.

SYS5CMP {} S 47 Non-Megistos System #5: company

 Optional address of the remote system (line 1 of 2).

SYS5AD1 {} S 47 Non-Megistos System #5: address (line 1)

 Optional address of the remote system (line 2 of 2).

SYS5AD2 {} S 47 Non-Megistos System #5: address (line 2)

 City the remote system lives in. Optional.

SYS5CTY {} S 47 Non-Megistos System #5: city

 A voice contact number. Optional.

SYS5VPH {} S 47 Non-Megistos System #5: voice phone number

 A data number for direct connections, if this is a BBS or an ISP.

SYS5DPH {} S 47 Non-Megistos System #5: data phone number

 The hostname of the remote system. Obligatory: if you leave this
 out, System #5 will not be registered since we won't know where to
 connect to. The address is either in dotted quad form, or a
 fully qualified host and domain name. For example: 10.153.9.27 and
 telnet.bigbbs.com are both acceptable. DNS resolution is be the
 client's responsibility, so be sure the hostname is correct!

SYS5HST {} S 79 Non-Megistos System #5: Internet hostname

 This is the port to which we'll connect. Port 23 is the port
 allocated to the standard telnet service. This is the part after
 the color (:) in a telnet:// url. The default is 23 -- leave it
 there if you don't know a port number.

SYS5PRT {Non-Megistos System #5: Telnet port to use (25=normal telnet): 23} N 0 65535

  The URL of the official web page of the system. Optional.

SYS5URL {} S 128 Non-Megistos System #5: Official web page URL (if any)

  The email address of someone who supports this system. Optional.

SYS5EML {} S 80 Non-Megistos System #5: Support email address (if any)

 The 'information package' MetaBBS sends to other interested systems
 contains an optional ASCII art ad of the system. Only the first 8192 bytes
 will be transmitted, to save bandwidth.  The ad is presented to users who
 expressly request more info on your BBS before connecting. List good points
 and keep it short and sweet. You can leave this empty if you can't be
 bothered to write information on remote systems.

SYS5ADV {} T Non-Megistos System #5: detailed description (<8192 bytes)

 This is a list of all the other MetaBBS-aware BBSs you'll allow telnet
 access from.  This does not apply to individual people using their own
 telnet clients from home, but entire systems that might allow their users
 to connect to you through the MetaBBS client. Entire systems providing a
 telnet access to this system will not be stopped, either. For a more
 restrictive and generic access list, have a look at the TCP wrapper,
 tcpd, and its access list files, /etc/hosts.allow and /etc/hosts.deny.

 The access list is a space-delimited list of Internet host addresses (eg
 10.159.34.3 or bbs.soup.com), or BBS addresses (each host may run more than
 one BBS, that's why we need MetaBBS in the first place). BBS addresses are
 host addresses followed by a slash and a BBS codename (e.g
 10.159.34.3/CRAZY or vennea.demon.co.uk/MEGISTOS).
 For a BBS to connect, it must pass both the ALLOW and DENY filters.

 Leave this field empty if you wish to allow *everyone* access. There's no
 point specifying anything here if this isn't one of your own systems:
 chances are, the remote system will have its own security set up.

SYS5ALW {} S 256 Non-Megistos System #5: hosts/BBSs allowed connections

 This is a list of MetaBBS-aware BBSs you do NOT want to allow telnet
 access from.  This does not apply to individual people using their own
 telnet clients from home, but entire systems that might allow their users
 to connect to you through the MetaBBS client. Entire systems providing a
 telnet access to this system will not be stopped, either. For a more
 restrictive and generic access list, have a look at the TCP wrapper,
 tcpd, and its access list files, /etc/hosts.allow and /etc/hosts.deny.

 The access list is a space-delimited list of Internet host addresses (eg
 10.159.34.3 or bbs.soup.com), or BBS addresses (each host may run more than
 one BBS, that's why we need MetaBBS in the first place). BBS addresses are
 host addresses followed by a slash and a BBS codename (e.g
 10.159.34.3/CRAZY or vennea.demon.co.uk/MEGISTOS).
 For a BBS to connect, it must pass both the ALLOW and DENY filters.

 Leave this field empty if you don't want to disallow access to anyone.
 There's no point specifying anything here if this isn't one of your own
 systems: chances are, the remote system will have its own security set up.

SYS5DNY {} S 256 Non-Megistos System #5: hosts/BBSs denied connections

  Normally, the local line is disconnected after a MetaBBS remote session is
  terminated. Set this to NO if you have *GOOD* reasons to do so (eg the
  Non-Megistos system is often too busy to accept connections, and users are
  annoyed at being disconnected just because of that). Bear in mind that
  this is only a *suggestion* sent to the remote MetaBBS client. It's that
  client that ultimately gets to decide whether to disconnect its users or
  not.

SYS5HUP {Non-Megistos System #5: disconnect line after remote session terminates? YES} B












 Apart from our own, local Megistos-based BBSs, we can register additional
 local or remote systems that aren't running Megistos (eg Unix shell hosts,
 MUDs, etc). This is done by filling in the required information in this and
 the next fields. This field is the codename of the remote system. It's only
 used in the MetaBBS client. Make it descriptive. If not specified, this
 system won't be registered at all.

SYS6COD {} S 8 Non-Megistos System #6: codename (empty=disable System #6)

 This is a longer, descriptive title for System #6. Include the hostname if
 you can, so that users will know where they're about to connect in case
 they want to do it on their own, without tying up one of our lines.

SYS6TTL {} S 51 Non-Megistos System #6: title

 Optional company name of the remote system.

SYS6CMP {} S 47 Non-Megistos System #6: company

 Optional address of the remote system (line 1 of 2).

SYS6AD1 {} S 47 Non-Megistos System #6: address (line 1)

 Optional address of the remote system (line 2 of 2).

SYS6AD2 {} S 47 Non-Megistos System #6: address (line 2)

 City the remote system lives in. Optional.

SYS6CTY {} S 47 Non-Megistos System #6: city

 A voice contact number. Optional.

SYS6VPH {} S 47 Non-Megistos System #6: voice phone number

 A data number for direct connections, if this is a BBS or an ISP.

SYS6DPH {} S 47 Non-Megistos System #6: data phone number

 The hostname of the remote system. Obligatory: if you leave this
 out, System #6 will not be registered since we won't know where to
 connect to. The address is either in dotted quad form, or a
 fully qualified host and domain name. For example: 10.153.9.27 and
 telnet.bigbbs.com are both acceptable. DNS resolution is be the
 client's responsibility, so be sure the hostname is correct!

SYS6HST {} S 79 Non-Megistos System #6: Internet hostname

 This is the port to which we'll connect. Port 23 is the port
 allocated to the standard telnet service. This is the part after
 the color (:) in a telnet:// url. The default is 23 -- leave it
 there if you don't know a port number.

SYS6PRT {Non-Megistos System #6: Telnet port to use (25=normal telnet): 23} N 0 65535

  The URL of the official web page of the system. Optional.

SYS6URL {} S 128 Non-Megistos System #6: Official web page URL (if any)

  The email address of someone who supports this system. Optional.

SYS6EML {} S 80 Non-Megistos System #6: Support email address (if any)

 The 'information package' MetaBBS sends to other interested systems
 contains an optional ASCII art ad of the system. Only the first 8192 bytes
 will be transmitted, to save bandwidth.  The ad is presented to users who
 expressly request more info on your BBS before connecting. List good points
 and keep it short and sweet. You can leave this empty if you can't be
 bothered to write information on remote systems.

SYS6ADV {} T Non-Megistos System #6: detailed description (<8192 bytes)

 This is a list of all the other MetaBBS-aware BBSs you'll allow telnet
 access from.  This does not apply to individual people using their own
 telnet clients from home, but entire systems that might allow their users
 to connect to you through the MetaBBS client. Entire systems providing a
 telnet access to this system will not be stopped, either. For a more
 restrictive and generic access list, have a look at the TCP wrapper,
 tcpd, and its access list files, /etc/hosts.allow and /etc/hosts.deny.

 The access list is a space-delimited list of Internet host addresses (eg
 10.159.34.3 or bbs.soup.com), or BBS addresses (each host may run more than
 one BBS, that's why we need MetaBBS in the first place). BBS addresses are
 host addresses followed by a slash and a BBS codename (e.g
 10.159.34.3/CRAZY or vennea.demon.co.uk/MEGISTOS).
 For a BBS to connect, it must pass both the ALLOW and DENY filters.

 Leave this field empty if you wish to allow *everyone* access. There's no
 point specifying anything here if this isn't one of your own systems:
 chances are, the remote system will have its own security set up.

SYS6ALW {} S 256 Non-Megistos System #6: hosts/BBSs allowed connections

 This is a list of MetaBBS-aware BBSs you do NOT want to allow telnet
 access from.  This does not apply to individual people using their own
 telnet clients from home, but entire systems that might allow their users
 to connect to you through the MetaBBS client. Entire systems providing a
 telnet access to this system will not be stopped, either. For a more
 restrictive and generic access list, have a look at the TCP wrapper,
 tcpd, and its access list files, /etc/hosts.allow and /etc/hosts.deny.

 The access list is a space-delimited list of Internet host addresses (eg
 10.159.34.3 or bbs.soup.com), or BBS addresses (each host may run more than
 one BBS, that's why we need MetaBBS in the first place). BBS addresses are
 host addresses followed by a slash and a BBS codename (e.g
 10.159.34.3/CRAZY or vennea.demon.co.uk/MEGISTOS).
 For a BBS to connect, it must pass both the ALLOW and DENY filters.

 Leave this field empty if you don't want to disallow access to anyone.
 There's no point specifying anything here if this isn't one of your own
 systems: chances are, the remote system will have its own security set up.

SYS6DNY {} S 256 Non-Megistos System #6: hosts/BBSs denied connections

  Normally, the local line is disconnected after a MetaBBS remote session is
  terminated. Set this to NO if you have *GOOD* reasons to do so (eg the
  Non-Megistos system is often too busy to accept connections, and users are
  annoyed at being disconnected just because of that). Bear in mind that
  this is only a *suggestion* sent to the remote MetaBBS client. It's that
  client that ultimately gets to decide whether to disconnect its users or
  not.

SYS6HUP {Non-Megistos System #6: disconnect line after remote session terminates? YES} B












 Apart from our own, local Megistos-based BBSs, we can register additional
 local or remote systems that aren't running Megistos (eg Unix shell hosts,
 MUDs, etc). This is done by filling in the required information in this and
 the next fields. This field is the codename of the remote system. It's only
 used in the MetaBBS client. Make it descriptive. If not specified, this
 system won't be registered at all.

SYS7COD {} S 8 Non-Megistos System #7: codename (empty=disable System #7)

 This is a longer, descriptive title for System #7. Include the hostname if
 you can, so that users will know where they're about to connect in case
 they want to do it on their own, without tying up one of our lines.

SYS7TTL {} S 51 Non-Megistos System #7: title

 Optional company name of the remote system.

SYS7CMP {} S 47 Non-Megistos System #7: company

 Optional address of the remote system (line 1 of 2).

SYS7AD1 {} S 47 Non-Megistos System #7: address (line 1)

 Optional address of the remote system (line 2 of 2).

SYS7AD2 {} S 47 Non-Megistos System #7: address (line 2)

 City the remote system lives in. Optional.

SYS7CTY {} S 47 Non-Megistos System #7: city

 A voice contact number. Optional.

SYS7VPH {} S 47 Non-Megistos System #7: voice phone number

 A data number for direct connections, if this is a BBS or an ISP.

SYS7DPH {} S 47 Non-Megistos System #7: data phone number

 The hostname of the remote system. Obligatory: if you leave this
 out, System #7 will not be registered since we won't know where to
 connect to. The address is either in dotted quad form, or a
 fully qualified host and domain name. For example: 10.153.9.27 and
 telnet.bigbbs.com are both acceptable. DNS resolution is be the
 client's responsibility, so be sure the hostname is correct!

SYS7HST {} S 79 Non-Megistos System #7: Internet hostname

 This is the port to which we'll connect. Port 23 is the port
 allocated to the standard telnet service. This is the part after
 the color (:) in a telnet:// url. The default is 23 -- leave it
 there if you don't know a port number.

SYS7PRT {Non-Megistos System #7: Telnet port to use (25=normal telnet): 23} N 0 65535

  The URL of the official web page of the system. Optional.

SYS7URL {} S 128 Non-Megistos System #7: Official web page URL (if any)

  The email address of someone who supports this system. Optional.

SYS7EML {} S 80 Non-Megistos System #7: Support email address (if any)

 The 'information package' MetaBBS sends to other interested systems
 contains an optional ASCII art ad of the system. Only the first 8192 bytes
 will be transmitted, to save bandwidth.  The ad is presented to users who
 expressly request more info on your BBS before connecting. List good points
 and keep it short and sweet. You can leave this empty if you can't be
 bothered to write information on remote systems.

SYS7ADV {} T Non-Megistos System #7: detailed description (<8192 bytes)

 This is a list of all the other MetaBBS-aware BBSs you'll allow telnet
 access from.  This does not apply to individual people using their own
 telnet clients from home, but entire systems that might allow their users
 to connect to you through the MetaBBS client. Entire systems providing a
 telnet access to this system will not be stopped, either. For a more
 restrictive and generic access list, have a look at the TCP wrapper,
 tcpd, and its access list files, /etc/hosts.allow and /etc/hosts.deny.

 The access list is a space-delimited list of Internet host addresses (eg
 10.159.34.3 or bbs.soup.com), or BBS addresses (each host may run more than
 one BBS, that's why we need MetaBBS in the first place). BBS addresses are
 host addresses followed by a slash and a BBS codename (e.g
 10.159.34.3/CRAZY or vennea.demon.co.uk/MEGISTOS).
 For a BBS to connect, it must pass both the ALLOW and DENY filters.

 Leave this field empty if you wish to allow *everyone* access. There's no
 point specifying anything here if this isn't one of your own systems:
 chances are, the remote system will have its own security set up.

SYS7ALW {} S 256 Non-Megistos System #7: hosts/BBSs allowed connections

 This is a list of MetaBBS-aware BBSs you do NOT want to allow telnet
 access from.  This does not apply to individual people using their own
 telnet clients from home, but entire systems that might allow their users
 to connect to you through the MetaBBS client. Entire systems providing a
 telnet access to this system will not be stopped, either. For a more
 restrictive and generic access list, have a look at the TCP wrapper,
 tcpd, and its access list files, /etc/hosts.allow and /etc/hosts.deny.

 The access list is a space-delimited list of Internet host addresses (eg
 10.159.34.3 or bbs.soup.com), or BBS addresses (each host may run more than
 one BBS, that's why we need MetaBBS in the first place). BBS addresses are
 host addresses followed by a slash and a BBS codename (e.g
 10.159.34.3/CRAZY or vennea.demon.co.uk/MEGISTOS).
 For a BBS to connect, it must pass both the ALLOW and DENY filters.

 Leave this field empty if you don't want to disallow access to anyone.
 There's no point specifying anything here if this isn't one of your own
 systems: chances are, the remote system will have its own security set up.

SYS7DNY {} S 256 Non-Megistos System #7: hosts/BBSs denied connections

  Normally, the local line is disconnected after a MetaBBS remote session is
  terminated. Set this to NO if you have *GOOD* reasons to do so (eg the
  Non-Megistos system is often too busy to accept connections, and users are
  annoyed at being disconnected just because of that). Bear in mind that
  this is only a *suggestion* sent to the remote MetaBBS client. It's that
  client that ultimately gets to decide whether to disconnect its users or
  not.

SYS7HUP {Non-Megistos System #7: disconnect line after remote session terminates? YES} B












 Apart from our own, local Megistos-based BBSs, we can register additional
 local or remote systems that aren't running Megistos (eg Unix shell hosts,
 MUDs, etc). This is done by filling in the required information in this and
 the next fields. This field is the codename of the remote system. It's only
 used in the MetaBBS client. Make it descriptive. If not specified, this
 system won't be registered at all.

SYS8COD {} S 8 Non-Megistos System #8: codename (empty=disable System #8)

 This is a longer, descriptive title for System #8. Include the hostname if
 you can, so that users will know where they're about to connect in case
 they want to do it on their own, without tying up one of our lines.

SYS8TTL {} S 51 Non-Megistos System #8: title

 Optional company name of the remote system.

SYS8CMP {} S 47 Non-Megistos System #8: company

 Optional address of the remote system (line 1 of 2).

SYS8AD1 {} S 47 Non-Megistos System #8: address (line 1)

 Optional address of the remote system (line 2 of 2).

SYS8AD2 {} S 47 Non-Megistos System #8: address (line 2)

 City the remote system lives in. Optional.

SYS8CTY {} S 47 Non-Megistos System #8: city

 A voice contact number. Optional.

SYS8VPH {} S 47 Non-Megistos System #8: voice phone number

 A data number for direct connections, if this is a BBS or an ISP.

SYS8DPH {} S 47 Non-Megistos System #8: data phone number

 The hostname of the remote system. Obligatory: if you leave this
 out, System #8 will not be registered since we won't know where to
 connect to. The address is either in dotted quad form, or a
 fully qualified host and domain name. For example: 10.153.9.27 and
 telnet.bigbbs.com are both acceptable. DNS resolution is be the
 client's responsibility, so be sure the hostname is correct!

SYS8HST {} S 79 Non-Megistos System #8: Internet hostname

 This is the port to which we'll connect. Port 23 is the port
 allocated to the standard telnet service. This is the part after
 the color (:) in a telnet:// url. The default is 23 -- leave it
 there if you don't know a port number.

SYS8PRT {Non-Megistos System #8: Telnet port to use (25=normal telnet): 23} N 0 65535

  The URL of the official web page of the system. Optional.

SYS8URL {} S 128 Non-Megistos System #8: Official web page URL (if any)

  The email address of someone who supports this system. Optional.

SYS8EML {} S 80 Non-Megistos System #8: Support email address (if any)

 The 'information package' MetaBBS sends to other interested systems
 contains an optional ASCII art ad of the system. Only the first 8192 bytes
 will be transmitted, to save bandwidth.  The ad is presented to users who
 expressly request more info on your BBS before connecting. List good points
 and keep it short and sweet. You can leave this empty if you can't be
 bothered to write information on remote systems.

SYS8ADV {} T Non-Megistos System #8: detailed description (<8192 bytes)

 This is a list of all the other MetaBBS-aware BBSs you'll allow telnet
 access from.  This does not apply to individual people using their own
 telnet clients from home, but entire systems that might allow their users
 to connect to you through the MetaBBS client. Entire systems providing a
 telnet access to this system will not be stopped, either. For a more
 restrictive and generic access list, have a look at the TCP wrapper,
 tcpd, and its access list files, /etc/hosts.allow and /etc/hosts.deny.

 The access list is a space-delimited list of Internet host addresses (eg
 10.159.34.3 or bbs.soup.com), or BBS addresses (each host may run more than
 one BBS, that's why we need MetaBBS in the first place). BBS addresses are
 host addresses followed by a slash and a BBS codename (e.g
 10.159.34.3/CRAZY or vennea.demon.co.uk/MEGISTOS).
 For a BBS to connect, it must pass both the ALLOW and DENY filters.

 Leave this field empty if you wish to allow *everyone* access. There's no
 point specifying anything here if this isn't one of your own systems:
 chances are, the remote system will have its own security set up.

SYS8ALW {} S 256 Non-Megistos System #8: hosts/BBSs allowed connections

 This is a list of MetaBBS-aware BBSs you do NOT want to allow telnet
 access from.  This does not apply to individual people using their own
 telnet clients from home, but entire systems that might allow their users
 to connect to you through the MetaBBS client. Entire systems providing a
 telnet access to this system will not be stopped, either. For a more
 restrictive and generic access list, have a look at the TCP wrapper,
 tcpd, and its access list files, /etc/hosts.allow and /etc/hosts.deny.

 The access list is a space-delimited list of Internet host addresses (eg
 10.159.34.3 or bbs.soup.com), or BBS addresses (each host may run more than
 one BBS, that's why we need MetaBBS in the first place). BBS addresses are
 host addresses followed by a slash and a BBS codename (e.g
 10.159.34.3/CRAZY or vennea.demon.co.uk/MEGISTOS).
 For a BBS to connect, it must pass both the ALLOW and DENY filters.

 Leave this field empty if you don't want to disallow access to anyone.
 There's no point specifying anything here if this isn't one of your own
 systems: chances are, the remote system will have its own security set up.

SYS8DNY {} S 256 Non-Megistos System #8: hosts/BBSs denied connections

  Normally, the local line is disconnected after a MetaBBS remote session is
  terminated. Set this to NO if you have *GOOD* reasons to do so (eg the
  Non-Megistos system is often too busy to accept connections, and users are
  annoyed at being disconnected just because of that). Bear in mind that
  this is only a *suggestion* sent to the remote MetaBBS client. It's that
  client that ultimately gets to decide whether to disconnect its users or
  not.

SYS8HUP {Non-Megistos System #8: disconnect line after remote session terminates? YES} B












 Apart from our own, local Megistos-based BBSs, we can register additional
 local or remote systems that aren't running Megistos (eg Unix shell hosts,
 MUDs, etc). This is done by filling in the required information in this and
 the next fields. This field is the codename of the remote system. It's only
 used in the MetaBBS client. Make it descriptive. If not specified, this
 system won't be registered at all.

SYS9COD {} S 8 Non-Megistos System #9: codename (empty=disable System #9)

 This is a longer, descriptive title for System #9. Include the hostname if
 you can, so that users will know where they're about to connect in case
 they want to do it on their own, without tying up one of our lines.

SYS9TTL {} S 51 Non-Megistos System #9: title

 Optional company name of the remote system.

SYS9CMP {} S 47 Non-Megistos System #9: company

 Optional address of the remote system (line 1 of 2).

SYS9AD1 {} S 47 Non-Megistos System #9: address (line 1)

 Optional address of the remote system (line 2 of 2).

SYS9AD2 {} S 47 Non-Megistos System #9: address (line 2)

 City the remote system lives in. Optional.

SYS9CTY {} S 47 Non-Megistos System #9: city

 A voice contact number. Optional.

SYS9VPH {} S 47 Non-Megistos System #9: voice phone number

 A data number for direct connections, if this is a BBS or an ISP.

SYS9DPH {} S 47 Non-Megistos System #9: data phone number

 The hostname of the remote system. Obligatory: if you leave this
 out, System #9 will not be registered since we won't know where to
 connect to. The address is either in dotted quad form, or a
 fully qualified host and domain name. For example: 10.153.9.27 and
 telnet.bigbbs.com are both acceptable. DNS resolution is be the
 client's responsibility, so be sure the hostname is correct!

SYS9HST {} S 79 Non-Megistos System #9: Internet hostname

 This is the port to which we'll connect. Port 23 is the port
 allocated to the standard telnet service. This is the part after
 the color (:) in a telnet:// url. The default is 23 -- leave it
 there if you don't know a port number.

SYS9PRT {Non-Megistos System #9: Telnet port to use (25=normal telnet): 23} N 0 65535

  The URL of the official web page of the system. Optional.

SYS9URL {} S 128 Non-Megistos System #9: Official web page URL (if any)

  The email address of someone who supports this system. Optional.

SYS9EML {} S 80 Non-Megistos System #9: Support email address (if any)

 The 'information package' MetaBBS sends to other interested systems
 contains an optional ASCII art ad of the system. Only the first 8192 bytes
 will be transmitted, to save bandwidth.  The ad is presented to users who
 expressly request more info on your BBS before connecting. List good points
 and keep it short and sweet. You can leave this empty if you can't be
 bothered to write information on remote systems.

SYS9ADV {} T Non-Megistos System #9: detailed description (<8192 bytes)

 This is a list of all the other MetaBBS-aware BBSs you'll allow telnet
 access from.  This does not apply to individual people using their own
 telnet clients from home, but entire systems that might allow their users
 to connect to you through the MetaBBS client. Entire systems providing a
 telnet access to this system will not be stopped, either. For a more
 restrictive and generic access list, have a look at the TCP wrapper,
 tcpd, and its access list files, /etc/hosts.allow and /etc/hosts.deny.

 The access list is a space-delimited list of Internet host addresses (eg
 10.159.34.3 or bbs.soup.com), or BBS addresses (each host may run more than
 one BBS, that's why we need MetaBBS in the first place). BBS addresses are
 host addresses followed by a slash and a BBS codename (e.g
 10.159.34.3/CRAZY or vennea.demon.co.uk/MEGISTOS).
 For a BBS to connect, it must pass both the ALLOW and DENY filters.

 Leave this field empty if you wish to allow *everyone* access. There's no
 point specifying anything here if this isn't one of your own systems:
 chances are, the remote system will have its own security set up.

SYS9ALW {} S 256 Non-Megistos System #9: hosts/BBSs allowed connections

 This is a list of MetaBBS-aware BBSs you do NOT want to allow telnet
 access from.  This does not apply to individual people using their own
 telnet clients from home, but entire systems that might allow their users
 to connect to you through the MetaBBS client. Entire systems providing a
 telnet access to this system will not be stopped, either. For a more
 restrictive and generic access list, have a look at the TCP wrapper,
 tcpd, and its access list files, /etc/hosts.allow and /etc/hosts.deny.

 The access list is a space-delimited list of Internet host addresses (eg
 10.159.34.3 or bbs.soup.com), or BBS addresses (each host may run more than
 one BBS, that's why we need MetaBBS in the first place). BBS addresses are
 host addresses followed by a slash and a BBS codename (e.g
 10.159.34.3/CRAZY or vennea.demon.co.uk/MEGISTOS).
 For a BBS to connect, it must pass both the ALLOW and DENY filters.

 Leave this field empty if you don't want to disallow access to anyone.
 There's no point specifying anything here if this isn't one of your own
 systems: chances are, the remote system will have its own security set up.

SYS9DNY {} S 256 Non-Megistos System #9: hosts/BBSs denied connections

  Normally, the local line is disconnected after a MetaBBS remote session is
  terminated. Set this to NO if you have *GOOD* reasons to do so (eg the
  Non-Megistos system is often too busy to accept connections, and users are
  annoyed at being disconnected just because of that). Bear in mind that
  this is only a *suggestion* sent to the remote MetaBBS client. It's that
  client that ultimately gets to decide whether to disconnect its users or
  not.

SYS9HUP {Non-Megistos System #9: disconnect line after remote session terminates? YES} B








