all:
	gcc -Iinclude src/*.c -o build/cbor
clean:
	rm build/cbor
