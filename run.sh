javac qmap/seg/SegmenterJni.java
$JAVA_HOME/bin/javah -classpath . -jni qmap.seg.SegmenterJni
jar cvfm segmenterjni.jar MANIFEST.MF qmap/seg/SegmenterJni.class
make clean
make
