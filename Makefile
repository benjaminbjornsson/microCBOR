alltests:
	gcc -Iinclude -Itests src/*.c tests/*.c -o build/cbor

clean:
	rm build/cbor
