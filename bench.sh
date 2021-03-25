#!/bin/bash

n=$1
image="$2"
w=100
h=200
outdir='tmp-bench'

usage() {
    echo "Usage: $0 n image"
    exit 1
}

if [ -z "$n" ] || [ -z "$image" ]; then
    usage
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