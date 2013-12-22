#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "encrypt.h"

#include <openssl/rand.h>
#include <openssl/rsa.h>
#include <openssl/engine.h>
#include <openssl/pem.h>
#include <openssl/err.h>

void read_ha_pub_key(){
	
	const char *b64_pKey = "-----BEGIN PUBLIC KEY-----\n"
  "MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQCjflVWCsBrOmlt3YWuw7PcDX/+\n"
  "pHbimzDBr50vBiq0JfxdBWv8E1H3rlmIV8gZd8DwGPMrfS40dXTBOtVaP3s7CVAk\n"
  "x9fDL8B9Mm9739v+36AN1COPntxucpOc9jfcqPo1S/2j/bqtC8un4whymdtDmGh3\n"
  "0GDMw4FoCaurQKfNIQIDAQAB\n"
  "-----END PUBLIC KEY-----\n";


	char   plainMsg[50];
	char   *encryptedMsg = NULL;
	char   *err;               // Buffer for any error messages

	FILE *keyfile = fopen("mykey.pub", "r");
	
	BIO* bio = BIO_new_mem_buf( (void*)publicKeyStr, -1 ) ;
	BIO_set_flags( bio, BIO_FLAGS_BASE64_NO_NL ) ;
	RSA* rsaPubKey = PEM_read_bio_RSA_PUBKEY( bio, NULL, NULL, NULL ) ;
	if( !rsaPubKey )
		printf( "ERROR: Could not load PUBLIC KEY!  PEM_read_bio_RSA_PUBKEY FAILED: %s\n", ERR_error_string( ERR_get_error(), NULL ) ) ;
	BIO_free( bio ) ;
	
	RSA *rsa_pub = PEM_read_RSA_PUBKEY(rsaPubKey, NULL, NULL, NULL);
	if(rsa_pub==NULL)
		ERR_print_errors_fp(stderr);
	else
		printf("we are good");
		
	strcpy(plainMsg, "Susitha Ravinda Senarath\0");
		
	/*char *modulus,*exp;
		
	BN_bn2bin(rsa_pub->n, (unsigned char *)modulus);
	BN_bn2bin(rsa_pub->e, (unsigned char *)exp);
	printf("\n%s\n%s\n", exp, modulus);	*/
		
	/*
	int encrypt_len;
    	err = malloc(130);
	printf("Plain message : %s\n",plainMsg);
	encrypt_len = RSA_public_encrypt(strlen(plainMsg), (unsigned char*)plainMsg, (unsigned char*)encryptedMsg, rsa_pub, RSA_PKCS1_OAEP_PADDING);
	printf("testtt\n");
    	if(encrypt_len == -1) {
    		
		printf("huta error\n");
		ERR_load_crypto_strings();
		ERR_error_string(ERR_get_error(), err);
		fprintf(stderr, "Error encrypting message: %s\n", err);
    	}
    	printf("test\n");
        printf("Encrypted :%s\n",encryptedMsg);*/
        
        int rsaLen = RSA_size( rsaPubKey ) ;
  	unsigned char* ed = (unsigned char*)malloc( rsaLen ) ;
  
  	// RSA_public_encrypt() returns the size of the encrypted data
  	// (i.e., RSA_size(rsa)). RSA_private_decrypt() 
  	// returns the size of the recovered plaintext.
  	*resultLen = RSA_public_encrypt( dataSize, (const unsigned char*)plainMsg, ed, pubKey, PADDING ) ; 
  	if( *resultLen == -1 )
    		printf("ERROR: RSA_public_encrypt: %s\n", ERR_error_string(ERR_get_error(), NULL));
}
