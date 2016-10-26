package qmap.seg;
public class SegmenterJni{
    private static boolean lib_flag = false;
    private String lib;
    private String conf;
    public SegmenterJni(String lib, String libpath, String conf){
        this.lib = lib;
        this.conf = conf;
        if(!lib_flag){
            System.out.println(this.lib);
            System.setProperty("java.library.path", libpath);
            System.load(this.lib);
            lib_flag = true;
            System.out.println("load so!!!!");
        }
    }
    public String segment(String str){
        return segment(str, this.conf);
    }
    public native String segment(String str, String conf);
    public static void main(String[] args){
        SegmenterJni jni = new SegmenterJni("/home/zhuhang-xy/segment_jni/SegmentJni/libsegmenterjni.so", "/home/zhuhang-xy/segment_jni/SegmentJni/" ,"/home/zhuhang-xy/segment_jni/conf/qsegconf.ini");
        System.out.println(jni.segment("中华人民共和国万岁"));
        System.out.println(jni.segment("中华人民共和国  good！"));
        //System.out.println(System.getProperty("java.library.path"));
    }
}
