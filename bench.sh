#!/bin/bash

n=$1
image='/home/rodolfo/dev/xompass/xompass-xm-xlpr/mock/tinta.jpg'
w=100
h=200
outdir='tmp-bench'

if [ -z "$n" ]; then
    echo "Usage: $0 n"
    exit 1
fi

mkdir -p $outdir

begin=$(date +%s)
for i in $(seq $n); do
    ./cvresize/resize $image $w $h >"$outdir/cpp$i.jpg"
done
end=$(date +%s)
echo "cpp : $((end-begin))s"

begin=$(date +%s)
for i in $(seq $n); do
    ./target/release/cxx-interop-cv-resize -w $w -h $h $image >"$outdir/rs$i.jpg"
done
end=$(date +%s)
echo "rs  : $((end-begin))s"

>&2 echo "Press [Enter] to exit"
read

rm -rf $outdir