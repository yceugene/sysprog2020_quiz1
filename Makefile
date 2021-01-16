CC = gcc

wk01Test: wk01Test.c ansWK01Test.h
	$(CC) wk01Test.c ansWK01Test.h -o wk01Test

wk01Test_P: wk01Test_P.c ansWK01Test.h
	$(CC) wk01Test_P.c ansWK01Test.h -o wk01Test_P

wk01Test_R: wk01Test_R.c ansWK01Test.h
	$(CC) wk01Test_R.c ansWK01Test.h -o wk01Test_R

# .PHONY: clean
clean:
	@rm -f *.o
	@rm -f wk01Test_R
	@rm -f wk01Test_R
	@rm -f wk01Test_R
