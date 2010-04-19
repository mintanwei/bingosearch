g++ -o crawler main.cpp crawler.cpp -I ../third_party/curl/include -I ../common/ -L ../third_party/curl/lib -lcurl -DLOG_LEVEL=0
