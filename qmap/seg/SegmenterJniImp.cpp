#include "SegmenterJni.h"
#include <jni.h>
#include "segmenter.h"
#include "config.h"
#include <iostream>
#include <string.h>
#include <vector>
#include "transcode.h"

using namespace std;

JNIEXPORT jstring JNICALL Java_SegmenterJni_segment
  (JNIEnv *env, jobject obj, jstring str, jstring conf)
{
    const char* org = env->GetStringUTFChars(str, false);
    const char* ini = env->GetStringUTFChars(conf, false);

    qss::segmenter::Config::get_instance()->init(ini);
    qss::segmenter::Segmenter *segmenter = qss::segmenter::CreateSegmenter();

    int org_len = strlen(org);
    std::cout << "org query: " << org << endl;
    std::cout << "org query len: " << org_len << endl;
    uint16_t *wbuf = new uint16_t[2048];
    int len = convToucs2(org, org_len, wbuf, 2048, qsrch_code_utf8);
    wbuf[len] = 0;

    char obuf[2048];
    uint16_t tbuf[2048];
    len = segmenter->segmentUnicode(wbuf, len, tbuf, 2048);
    int l = convFromucs2(tbuf, len, obuf, 2048, qsrch_code_utf8);
    obuf[l] = '\0';
    /*qss::segmenter::word_t longWords[org_len * 2];
    qss::segmenter::word_t shortWords[org_len * 2];
    segmenter->segment(wbuf, len, longWords, shortWords);

    std::string tmp_result;
    char buf[1024];
    int token_len;
    for(int i = 0, n = 0; i < len; i += n){
        n = longWords[i].len;
        token_len = convFromucs2(wbuf + longWords[i].ol_core_start, n, buf, 1024, qsrch_code_utf8);
        buf[token_len] = 0;
        tmp_result += string(buf);
        tmp_result += " ";
        for(int j = i + 1; j < i + n; j++){
            longWords[j].len = 0;
        }
    }

    tmp_result += "---------";

    for(int i = 0, n = 0; i < len; i += n){
        n = shortWords[i].len;
        token_len = convFromucs2(wbuf + shortWords[i].ol_core_start, n, buf, 1024, qsrch_code_utf8);
        buf[token_len] = 0;
        tmp_result += string(buf);
        tmp_result += " ";
        for(int j = i + 1; j < i + n; j++){
            shortWords[j].len = 0;
        }
    }*/
    env->ReleaseStringUTFChars(str, org);
    env->ReleaseStringUTFChars(conf, ini);
    jstring result = env->NewStringUTF(obuf);
    delete [] wbuf;
    return result;
}
             
