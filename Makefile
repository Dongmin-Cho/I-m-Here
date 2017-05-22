install:
	cd face_recognition/src/; mkdir build; cd build; cmake ..; make; cp ../*.dat .;
clean:
	rm -rf face_recognition/src/build;
