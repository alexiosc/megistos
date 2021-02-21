#!/bin/sh
echo <<EOF

mogrify -verbose -crop 720x480+20+76 +repage -borderColor '#222' -border 40x40 -filter point -resize 200% *png

EOF
