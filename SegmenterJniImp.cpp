#include "qmap_seg_SegmenterJni.h"
#include <jni.h>
#include "segmenter.h"
#include "config.h"
#include <iostream>
#include <string.h>
#include <vector>
#include "transcode.h"

using namespace std;


__thread qss::segmenter::Segmenter *segmenter = NULL;
JNIEXPORT jstring JNICALL Java_qmap_seg_SegmenterJni_segment
  (JNIEnv *env, jobject obj, jstring str, jstring conf)
{
    const char* org = env->GetStringUTFChars(str, false);
    const char* ini = env->GetStringUTFChars(conf, false);
    if(segmenter == NULL){
        qss::segmenter::Config::get_instance()->init(ini);
        segmenter = qss::segmenter::CreateSegmenter();
        cout << "Create Segmenter!" << endl;
    }

    int org_len = strlen(org);
    uint16_t wbuf[2048];
    int len = convToucs2(org, org_len, wbuf, 2048, qsrch_code_utf8);
    wbuf[len] = 0;

    char obuf[2048];
    uint16_t tbuf[2048];
    len = segmenter->segmentUnicode(wbuf, len, tbuf, 2048);
    int l = convFromucs2(tbuf, len, obuf, 2048, qsrch_code_utf8);
    obuf[l] = '\0';
    env->ReleaseStringUTFChars(str, org);
    env->ReleaseStringUTFChars(conf, ini);
    env->DeleteLocalRef(str);
    env->DeleteLocalRef(conf);
    jstring result = env->NewStringUTF(obuf);
    return result;
}
