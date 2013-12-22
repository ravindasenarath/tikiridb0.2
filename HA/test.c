//////////  Just a testing code  -- Ignore this


#include <stdio.h>
#include <stdlib.h>
#include "DB/getUsrPubKey.h"
#include "generateTicket.h"
//#include "encrypt2.h"
#include "security/security.h"


int main(int argc, char **argv){

  char * publicKey;
  char username[] = "nelka";
  char *sk2;
  char *encryptedSk2;

  publicKey = getPublicKey(username);  /* user's public key is needed to encrypt the SK2.  */
		
	if(publicKey != "")
	{
	   USR_TICKET ticket;
	   ticket = generateUsrTicket(username);   
	   
	   /* Enctypt the ticket by SK1 */
	   
	   /* Encrypt the SK2 by public key */
	   sk2 = ticket.sk2;
	   encryptedSk2 = encrypt_sk2 (sk2, publicKey);
	   
	   printf("Encrypted SK2: \n%s \n", encryptedSk2);
	
	}

  exit(0);
}


/*
http://www.openssl.org/docs/crypto/EVP_EncryptInit.html

*/

