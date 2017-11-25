#!/bin/sh
now_dir=`dirname $0`		# このファイルのディレクトリパスを取得
cd "${now_dir}/BlackJack/BlackJack/"
cp * ../../../vc/BlackJack/BlackJack/
cd ../../../vc/BlackJack/BlackJack/
nkf -s --overwrite ./*
