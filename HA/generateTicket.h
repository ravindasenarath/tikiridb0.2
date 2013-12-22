
/*

typedef struct ticket {	
	int ticketId;   
	char username[20];   
        char date[20];   
        int validityPeriod; 
        char sk2[16];   
        char attr[40][15]; 
        char duration[40][10];  
} USR_TICKET;

*/

/*
typedef struct {
 unsigned char data[1]; 
} nw_uint8_t;
*/

typedef struct ticket {	
	int ticketId;   /* ID of the ticket - 1 */
	char username[10];   /* client's username - 2 */
        char date[20];   /* ticket generated date - 3 */
        int validityPeriod;  /* lifetime of ticket - 4 */
        char sk2[16];   /* session key 2 (SK2) - 5 */
        char attr[10];  /* sensor data attibutes - 6 */
        char duration[10];  /* time duration from ticket generated date - 7 */
} USR_TICKET;

USR_TICKET generateUsrTicket (char usrname[], char * sk2, int count);
