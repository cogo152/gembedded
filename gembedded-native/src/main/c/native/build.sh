#!/bin/bash

sudo rm -rf build

cmake   --no-warn-unused-cli                        \
        -DCMAKE_BUILD_TYPE:STRING=Release           \
        -S.                                         \
        -B build                                    \
        -G "Unix Makefiles"                         \

cmake   --build build                               \
        --config Release                            \
        --target all                                \
        -j 14 --                                    \


sudo ctest -j6 -C Release -T test --output-on-failure --test-dir build  -R ^gembedded-native_test$

cmake   --build build                               \
        --config Release                            \
        --target install package                    \
        -j 14 --                                    \
