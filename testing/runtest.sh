#!/usr/bin/env bash

cd ../build
make -b
cd ../testing

cd build && make -b
./icp_test

cd ../..
./build/simpleicp -f testing/points_transformed.xyz -m testing/points.xyz
