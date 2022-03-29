all:
	make -C timerLib install
	make -C lcdLib install

clean:
	make -C timerLib clean
	make -C lcdLib clean
	rm -rf h lib
