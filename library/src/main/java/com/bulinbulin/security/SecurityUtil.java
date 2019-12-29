package com.bulinbulin.security;

public class SecurityUtil {

    public SecurityUtil(){
        System.loadLibrary("sec");
    }

    /**
     * 生成国密的公私钥对
     * @return KeyPairInfo对象
     */
    public native KeyPairInfo createKeyPair();




    /**
     * sm2加密算法，以C1C2C3模式拼接返回，采用推荐曲线
     * @param data  需要加密内容
     * @param key   加密的公钥，长度为65字节[国密SM2公钥规定十六进制以04开头]
     * @return      加密后经过hex编码后返回
     */
    public native byte[] sm2Encrypt(byte[] data, byte[] key);


    /**
     * sm2加密算法，以C1C2C3拼接传入，采用推荐曲线
     * @param data  需要解密的数据，此数据方法内部进行hex解码
     * @param key   解密的私钥，长度为32字节
     * @return  解密后的数据，以byte数组返回
     */
    public native byte[] sm2Decrypt(String data, byte[] key);



    /**
     * sm2加密算法，以C1C3C2模式拼接返回，采用推荐曲线
     * @param data  需要加密内容
     * @param key   加密的公钥，长度为64字节
     * @return      加密后经过hex编码后返回
     */
    public native byte[] sm2EncryptOld(byte[] data, byte[] key);


    /**
     * sm2加密算法，以C1C3C2拼接传入，采用推荐曲线
     * @param data  需要解密的数据，此数据方法内部进行hex解码
     * @param key   解密的私钥，长度为32字节
     * @return  解密后的数据，以byte数组返回
     */
    public native byte[] sm2DecryptOld(String data, byte[] key);










    /**
     * sm3加密
     * @param data 需要计算sm3的字节数组
     * @return 返回64长度的字符串
     */
    public native String sm3(byte[] data);


    /**
     * sm4加密,加密后的长度如果不满足16的倍数，则进行补位
     * @param data  需要加密的数据
     * @param key   加密的key
     * @return  sm4加密后进行base64加密然后进行返回
     */
    public native String sm4Encrypt(byte[] data, byte[] key);


    /**
     * sm4解密，解密先进行data的base64解密，然后再进行sm4解密
     * base64操作已经内部封装
     * @param data 解密的base64字符串
     * @param key  解密的秘钥
     * @return  sm4先进行base64解密再进行sm4解密
     */
    public native byte[] sm4Decrypt(byte[] data,byte[] key);


    /**
     * md5加密
     * @param data 需要进行md5的数据
     * @return  返回64长度的字符串
     */
    public native String md5(byte[] data);


    /**
     * byte[]->十六进制转换
     * @param data
     * @return 十六进制编码
     */
    public native String hexEncode(byte[] data);


    /**
     * 十六进制->byte[]转换
     * @param data  需要转换的十六进制字符串
     * @return 转换后的字节数组
     */
    public native byte[] hexDecode(String data);


    /**
     * base64加密
     * @param data 需要加密的数据（byte数组类型）
     * @return base64后的字符串
     */
    public native String base64Encode(byte[] data);

    /**
     * base64加密
     * @param data 需要解密的数据（ByteArray类型）
     * @return base64解密后的字节数组（ByteArray）
     */
    public native byte[] base64Decode(byte[] data);


    /**
     * 生成一个指定长度的随机数
     * @param len 生成随机数的长度
     * @return 生成指定长度随机数的字符串
     */
    public native String random(int len);



}
