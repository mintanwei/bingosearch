cd query_preprocessor
sh query_preprocessor.sh
cd ../crawler
./crawler
cd ../parser/
./parser.pl
cd ../image_downloader/
./image_downloader.pl
cd ../image_filter/
./image_filter.pl
cd ../visual_rank/
./visual_rank
cd ../index_builder/
./index_builder
