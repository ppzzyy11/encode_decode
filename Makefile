make:
	g++ -std=c++11 encode.cpp -o a.out
	g++ -std=c++11 decode.cpp -o b.out

encode:
	./a.out book.txt message.txt coded.txt

decode:
	./b.out book.txt coded.txt decoded.txt


