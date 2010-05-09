g++ -o crawler main.cpp crawler.cpp -I ../third_party/curl/include -I ../common/ -L ../third_party/curl/lib -L ../common/ -lcommon -lcurl -DLOG_LEVEL=0
