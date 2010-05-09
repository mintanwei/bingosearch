#g++ -c image_similarity*.cpp -I ../common/ -DLOG_LEVEL=0
#ar rc libimage_similarity.a image_similarity*.o

#g++ -c visual_rank.cpp -I ../common/ -DLOG_LEVEL=0
#ar rc libvisual_rank.a

#g++ -o visual_rank main.cpp -L . -lvisual_rank -limage_similarity -I ../common/ -DLOG_LEVEL=0
g++ -o visual_rank main.cpp visual_rank.cpp image_similarity*.cpp -I ../common/ -L ../common/ -l common -DLOG_LEVEL=0
