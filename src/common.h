/*

	TODO: Add all includes here.

*/

/**
 *	Maximale Paketgröße die zu erwarten ist.
 */
#define PACKAGE_SIZE_MAX 	1470

/**
 *	Maximale Paketgröße eines Acknowledgements.
 */
#define ACK_SIZE_MAX 		1

/**
 *	Anzahl der Fahrzeugdaten.
 */
#define DATA_NUM			401

/**
 *	Anzahl der Bytes die ein Datensatz im ursprünglichen Datenstrom belegt.
 */
#define DATA_NUM_OF_BYTES	2


/**
 *	IP-Adressen der Teilnehmer.
 */
#define EMBPC_IP	"127.0.0.1"
#define MABXII_IP	"127.0.0.1"
#define VSERVER_IP	"127.0.0.1"

/**
 *	Portnummern der Teilnehmer.
 */
#define MABXII_PORT			5000
#define MABXII_INFO_PORT	5001
#define EMBPC_PORT			5002
#define EMBPC_INFO_PORT		5003
#define VSERVER_PORT 		5004
#define VSERVER_INFO_PORT	5005																																																																																																																																																																																																																																																																																																																																																																		

/**
 *	Inhalte bestimmter Pakete.
 */
#define MSG_READY_1	{96}
#define MSG_READY_2 {97}




