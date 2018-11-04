pre-build:
	mkdir -p bin

build: src/*.java
	javac -d bin -cp lib/forms.jar $^

run: pre-build build
	java -cp bin:lib/forms.jar Server
