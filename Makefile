install:
	cd face_recognition/; make install; cd ..;cd caffe/;mkdir build;cd build;cmake ..;make;make;cd ../../;
clean:
	cd face_recognition/;make clean;cd ..;cd caffe/;make clean;cd ..;
