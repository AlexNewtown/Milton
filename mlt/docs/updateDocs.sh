cd /home/tfischer/course/cs197/docs/html && rm -f * && cd ../../src && doxygen ../docs/doxygenConfig && cd - && tar -cvf milton.tar * && gzip milton.tar && scp milton.tar.gz mlt224@milton.mjacobs.net:.
