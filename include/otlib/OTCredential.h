/*************************************************************
 *    
 *  OTCredential.h
 *  
 */
// A nym contains a list of master credentials, via OTCredential.
// The whole purpose of a Nym is to be an identity, which can have
// master credentials.

// Each credential is like a master key for the Nym's identity,
// which can issue its own subkeys.

// Each subkey has 3 key pairs: encryption, signing, and authentication.
// Not all subcredentials are a subkey. For example, you might have a
// subcredential that uses Google Authenticator, and thus doesn't contain
// any keys, because it uses alternate methods for its own authentication.

// Each OTCredential contains a "master" subkey, and a list of subcredentials
// (some of them subkeys) signed by that master.

// The same class (subcredential/subkey) is used because there are master
// credentials and subcredentials, so we're using inheritance for "subcredential"
// and "subkey" to encapsulate the credentials, so we don't have to repeat code
// across both.
// We're using a "has-a" model here, since the OTCredential "has a" master
// subkey, and also "has a" list of subcredentials, some of which are subkeys.

// Each subcredential must be signed by the subkey that is the master key.
// Each subkey has 3 key pairs: encryption, signing, and authentication.

// Each key pair has 2 OTAsymmetricKeys (public and private.)

// I'm thinking that the Nym should also have a key pair (for whatever is
// its current key pair, copied from its credentials.)

// the master should never be able to do any actions except for sign subkeys.
// the subkeys, meanwhile should only be able to do actions, and not issue
// any new keys.

/************************************************************
 -----BEGIN PGP SIGNED MESSAGE-----
 Hash: SHA256
 
 *                 OPEN TRANSACTIONS
 *
 *       Financial Cryptography and Digital Cash
 *       Library, Protocol, API, Server, and GUI 
 *    
 *    	 -- Anonymous Numbered Accounts.
 *    	 -- Untraceable Digital Cash.
 *    	 -- Triple-Signed Receipts.
 *    	 -- Cheques, Vouchers, Transfers, Inboxes.
 *    	 -- Basket Currencies, Markets, Payment Plans.
 *    	 -- Signed, XML, Ricardian-style Contracts.
 *    
 *  Copyright (C) 2010-2012 by "Fellow Traveler" (A pseudonym)
 *
 *  EMAIL:
 *  FellowTraveler@rayservers.net
 *  
 *  BITCOIN:  1NtTPVVjDsUfDWybS4BwvHpG2pdS9RnYyQ
 *
 *  KEY FINGERPRINT (PGP Key in license file):
 *  9DD5 90EB 9292 4B48 0484  7910 0308 00ED F951 BB8E
 *
 *  OFFICIAL PROJECT WIKI(s):
 *  https://github.com/FellowTraveler/Moneychanger
 *  https://github.com/FellowTraveler/Open-Transactions/wiki 
 *
 *  WEBSITE:
 *  http://www.OpenTransactions.org/
 *    
 *  Components and licensing:
 *   -- Moneychanger..A Java client GUI.....LICENSE:.....GPLv3
 *   -- OTLib.........A class library.......LICENSE:...LAGPLv3 
 *   -- OT-API........A client API..........LICENSE:...LAGPLv3
 *   -- testwallet....Command-line client...LICENSE:...LAGPLv3
 *   -- OT-Server.....Server Application....LICENSE:....AGPLv3
 *  Github.com/FellowTraveler/Open-Transactions/wiki/Components
 *
 *  All of the above OT components were designed and written by
 *  Fellow Traveler, with the exception of Moneychanger, which
 *  was contracted out to Vicky C (livewire_3001@yahoo.com).
 *
 *  -----------------------------------------------------
 *
 *   LICENSE:
 *   This program is free software: you can redistribute it
 *   and/or modify it under the terms of the GNU Affero
 *   General Public License as published by the Free Software
 *   Foundation, either version 3 of the License, or (at your
 *   option) any later version.
 *    
 *   ADDITIONAL PERMISSION under the GNU Affero GPL version 3
 *   section 7: (This paragraph applies only to the LAGPLv3
 *   components listed above.) If you modify this Program, or
 *   any covered work, by linking or combining it with other
 *   code, such other code is not for that reason alone subject
 *   to any of the requirements of the GNU Affero GPL version 3.
 *   (==> This means if you are only using the OT-API, then you
 *   don't have to open-source your code--only your changes to
 *   Open Transactions itself must be open source. Similar to
 *   LGPLv3, except it applies to software-as-a-service, not
 *   just to distributing binaries.)
 *
 *   Extra WAIVER for OpenSSL, Lucre, and all other libraries
 *   used by Open Transactions: This program is released under
 *   the AGPL with the additional exemption that compiling,
 *   linking, and/or using OpenSSL is allowed. The same is true
 *   for any other open source libraries included in this
 *   project: complete waiver from the AGPL is hereby granted to
 *   compile, link, and/or use them with Open Transactions,
 *   according to their own terms, as long as the rest of the
 *   Open Transactions terms remain respected, with regard to
 *   the Open Transactions code itself.
 *    
 *   Lucre License:
 *   This code is also "dual-license", meaning that Ben Lau-
 *   rie's license must also be included and respected, since
 *   the code for Lucre is also included with Open Transactions.
 *   See Open-Transactions/OTLib/Lucre/LUCRE_LICENSE.txt
 *   The Laurie requirements are light, but if there is any
 *   problem with his license, simply remove the Lucre code.
 *   Although there are no other blind token algorithms in Open
 *   Transactions (yet. credlib is coming), the other functions
 *   will continue to operate.
 *   -----------------------------------------------------
 *   You should have received a copy of the GNU Affero General
 *   Public License along with this program.  If not, see:
 *   http://www.gnu.org/licenses/
 *
 *   If you would like to use this software outside of the free
 *   software license, please contact FellowTraveler.
 *   (Unfortunately many will run anonymously and untraceably,
 *   so who could really stop them?)
 *   
 *   DISCLAIMER:
 *   This program is distributed in the hope that it will be
 *   useful, but WITHOUT ANY WARRANTY; without even the implied
 *   warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 *   PURPOSE.  See the GNU Affero General Public License for
 *   more details.
 -----BEGIN PGP SIGNATURE-----
 Version: GnuPG v1.4.11 (Darwin)
 
 iQIcBAEBCAAGBQJOjvvUAAoJEAMIAO35UbuOBlMP/1LX0xJ9CrTOe1G/mgc+VygT
 JPVZDAbQDL/lJXOZMbaPJ/GaLXyEnTViHp97ERrlVuBQz+9uonIKCmPqAGYGVBG1
 MGV2QcscXU2aOUT1VPf2OYEOIul0h8FX2lixfqouH9/OkVsGRLr79Zu8z3zdsO4R
 ktQtjZEU6lnL2t6cmp/cuXlQnbz1xvxd56xNDR11YP07Z4x+CuDB4EAK+P9TfCwn
 tqq5yJmxJM9HtMoi3cUU7kXodKm1n1YZt7O46DOxHqbXqErHChN1ekSK0fXad614
 Gmh+5JfvHjx5XoFWMxb46aAAcUiG8+QpFBcKtSYP2X96k1ylgxMCzrK60ec/MxKV
 BzvP00OJ6PzzrTlcUaCgJ8ZX+0scOMvW0XKioEorozKSWNFvT4Drc4Thhy8u9ET3
 ru1enNFrjdxKjw2+ZTQcKSZjSRx2kMQ2od/dkqUlhe/M1cHGhseH6ls7pItrkykE
 ufZ9GlZoxYE+FRatIBPneT9WwsvFFvH+i6cQ/MM9pbTr19g6VPzVZ4U9E65BbTDB
 czITynH+uMtJLbprtCdQlsI+vqTgYNoY8AUsmnr1qUkp020qGlvwfCJVrooisTmm
 yIh+Yp/KBzySU3inzclaAfv102/t5xi1l+GTyWHiwZxlyt5PBVglKWx/Ust9CIvN
 6h9BYZFTZrh/OwBXCdAv
 =MUfS
 -----END PGP SIGNATURE-----
 **************************************************************/


#ifndef __OT_CREDENTIAL_H__
#define __OT_CREDENTIAL_H__

#ifndef EXPORT
#define EXPORT
#endif
#include <ExportWrapper.h>

#ifdef _WIN32
#include <WinsockWrapper.h>
#endif


#include <map>

#include "OTContract.h"



// A nym contains a list of master credentials, via OTCredential.
// The whole purpose of a Nym is to be an identity, which can have
// master credentials.

// Each credential is like a master key for the Nym's identity,
// which can issue its own subkeys.

// Each subkey has 3 key pairs: encryption, signing, and authentication.
// Not all subcredentials are a subkey. For example, you might have a
// subcredential that uses Google Authenticator, and thus doesn't contain
// any keys, because it uses alternate methods for its own authentication.

// Each OTCredential contains a "master" subkey, and a list of subcredentials
// (some of them subkeys) signed by that master.

// The same class (subcredential/subkey) is used because there are master
// credentials and subcredentials, so we're using inheritance for "subcredential"
// and "subkey" to encapsulate the credentials, so we don't have to repeat code
// across both.
// We're using a "has-a" model here, since the OTCredential "has a" master
// subkey, and also "has a" list of subcredentials, some of which are subkeys.

// Each subcredential must be signed by the subkey that is the master key.
// Each subkey has 3 key pairs: encryption, signing, and authentication.

// Each key pair has 2 OTAsymmetricKeys (public and private.)

// I'm thinking that the Nym should also have a key pair (for whatever is
// its current key pair, copied from its credentials.)

// the master should never be able to do any actions except for sign subkeys.
// the subkeys, meanwhile should only be able to do actions, and not issue
// any new keys.

// ------------------------------------------------

class OTString;
class OTAsymmetricKey;


// Encapsulates public/private key (though often there may only be
// a public key present, unless the nym belongs to you.)
//
class OTKeypair
{
    friend class OTLowLevelKeyData;
    // --------------------------------------
    OTAsymmetricKey * m_pkeyPublic;     // This nym's public key
	OTAsymmetricKey * m_pkeyPrivate;	// This nym's private key
public:
    bool MakeNewKeypair(int nBits=1024);
    // ---------------------------------------------------------------
EXPORT	bool HasPublicKey();
EXPORT	bool HasPrivateKey();
    // -------------------------------------
EXPORT	const OTAsymmetricKey & GetPublicKey()  const;
		const OTAsymmetricKey & GetPrivateKey() const;
    // ------------------------------------------
    bool CalculateID(OTIdentifier & theOutput) const;
    // ---------------------------------------------------------------
    bool SaveCertToString      (OTString & strOutput);
    bool SavePrivateKeyToString(OTString & strOutput, const OTString * pstrReason=NULL);
    bool SaveCertAndPrivateKeyToString(OTString & strOutput, const OTString * pstrReason=NULL);
    // ---------------------------------------------------------------
    // Load from local storage.
    bool LoadPrivateKey(const OTString & strFoldername,
                        const OTString & strFilename, const OTString * pstrReason=NULL);
	bool LoadPublicKey (const OTString & strFoldername,
                        const OTString & strFilename);    
    // ***************************************************************
    // LoadPrivateKeyFromCertString
    //
    // "escaped" means pre-pended with "- " as in:   - -----BEGIN CERTIFICATE....
    //
    bool LoadPrivateKeyFromCertString(const OTString & strCert, bool bEscaped=true, const OTString * pstrReason=NULL);
    // ***************************************************************
    // Load Public Key from Cert (file or string)
    //
	bool LoadPublicKeyFromCertString(const OTString & strCert, bool bEscaped=true); // DOES handle bookends, AND escapes.
    bool LoadPublicKeyFromCertFile  (const OTString & strFoldername, const OTString & strFilename); // DOES handle bookends.
    // ---------------------------------------------------------------
    bool LoadCertAndPrivateKeyFromString(const OTString & strInput, const OTString * pstrReason=NULL);
    // ---------------------------------------------------------------
    // LOAD BOTH KEYS FROM CERT FILE
    //
    bool LoadBothKeysFromCertFile(const OTString & strFoldername,
                                  const OTString & strFilename, const OTString * pstrReason=NULL);
    
    bool SaveAndReloadBothKeysFromTempFile(OTString * pstrOutputCert=NULL, const OTString * pstrReason=NULL);
    // ***************************************************************************************
    // PUBLIC KEY

    // * Get the public key in ASCII-armored format                 -- OTASCIIArmor
	// * Get the public key in ASCII-armored format WITH bookends   -- OTString
	//       - ------- BEGIN PUBLIC KEY --------
	//       Notice the "- " before the rest of the bookend starts.
EXPORT	bool GetPublicKey(OTASCIIArmor & strKey) const;
EXPORT	bool GetPublicKey(OTString & strKey, bool bEscaped=true) const;
	// -----------------------------------------------------------------------
	// (Below) Decodes a public key from ASCII armor into an actual key pointer
	// and sets that as the m_pKey on this object.
EXPORT	bool SetPublicKey(const OTASCIIArmor & strKey);
EXPORT	bool SetPublicKey(const OTString & strKey, bool bEscaped=false);
	// (Above) Decodes a public key from bookended key string into an actual key
	// pointer, and sets that as the m_pPublicKey on this object.
	// This is the version that will handle the bookends ( -----BEGIN PUBLIC KEY-----)

    // ***************************************************************************************
    // PRIVATE KEY
	// Get the private key in ASCII-armored format with bookends 
	// - ------- BEGIN ENCRYPTED PRIVATE KEY --------
	// Notice the "- " before the rest of the bookend starts.
	bool GetPrivateKey(OTString & strKey, bool bEscaped=true) const;
	bool GetPrivateKey(OTASCIIArmor & strKey) const;  // Get the private key in ASCII-armored format
	
	// Decodes a private key from ASCII armor into an actual key pointer
	// and sets that as the m_pPrivateKey on this object.
	// This is the version that will handle the bookends ( -----BEGIN ENCRYPTED PRIVATE KEY-----)
	bool SetPrivateKey(const OTString & strKey, bool bEscaped=false);
	bool SetPrivateKey(const OTASCIIArmor & strKey); // Decodes a private key from ASCII armor into an actual key pointer and sets that as the m_pKey on this object.
    // ------------------------------------------------
    OTKeypair();
    ~OTKeypair();
};

// ***************************************************************************************

// This is stored as an OTContract, and it must be signed by the
// master key. (which is also an OTSubcredential.)
//
class OTSubcredential : public OTContract
{
private:  // Private prevents erroneous use by other classes.
    typedef OTContract ot_super;
public:
    
    OTSubcredential();
    virtual ~OTSubcredential();
    virtual void Release();
    void Release_Subcredential();
};

// ***************************************************************************************
/// OTSubkey
/// A form of OTSubcredential that contains 3 key pairs: signing, authentication, and encryption.
class OTSubkey : public OTSubcredential
{
private:  // Private prevents erroneous use by other classes.
    typedef OTSubcredential ot_super;
public:
    OTKeypair   m_SigningKey;  // Signing keys, for signing/verifying a "legal signature".
    OTKeypair   m_AuthentKey;  // Authentication keys, used for signing/verifying transmissions and stored files.
    OTKeypair   m_EncryptKey;  // Encryption keys, used for sealing/opening OTEnvelopes.
    
    OTSubkey();
    virtual ~OTSubkey();
    virtual void Release();
    void Release_Subkey();
};
// ***************************************************************************************

typedef OTSubkey OTMasterkey;

typedef std::map<int, OTSubcredential *> mapOfSubcredentials;

// ***************************************************************************************
// THE MASTER CREDENTIAL (below -- OTCredential)
//
// Contains a "master" subkey,
// and a list of subcredentials signed by that master.
// (Some of which are subkeys, since subkey inherits from
// subcredential.)
// Each subcredential can generate its own "credential" contract,
// even the master subcredential, so an OTCredential object
// actually may include many "credentials." (That is, each may be
// issued at separate times. Each may be registered on a server at
// separate times. Etc.)
//
// Each nym has multiple OTCredentials because there may be
// several master keys, each with their own subcredentials.
//
// ------------------------------------------------
class OTCredential
{    
private:
    OTMasterkey         * m_pMasterkey;
    mapOfSubcredentials   m_mapSubcredentials;
    
public:
    OTCredential();
    ~OTCredential();
};


// ***************************************************************************************
























#endif // __OT_CREDENTIAL_H__






/*
 
 http://stackoverflow.com/questions/9749560/how-to-calculate-x-509-certificates-sha-1-fingerprint-in-c-c-objective-c
 
 
 
 Question:
 
 How do you calculate the SHA1 hash/fingerprint of an X509 cert stored within
 a PEM file using C/C++/Objective-C?
 
 
 Answer:
 
 Here is a solution I found using the OpenSSL libraries.
 I am posting the question and answer on stack overflow
 in the hopes that it will save others the trouble and
 time of figuring it out themselves.

 
 
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/x509.h>
#include <openssl/bio.h>


int main(int argc, char * argv[])
{
   struct stat           sb;
   unsigned char       * buff;
   int                   fd;
   ssize_t               len;
   BIO                 * bio;
   X509                * x;
   unsigned              err;
   int                   pos;
   char                  errmsg[1024];
   const EVP_MD        * digest;
   unsigned char         md[EVP_MAX_MD_SIZE];
   unsigned int          n;

   // checks arguments
   if (argc != 2)
   {
      fprintf(stderr, "Usage: peminfo <pemfile>\n");
      return(1);
   };

   // checks file
   if ((stat(argv[1], &sb)) == -1)
   {
      perror("peminfo: stat()");
      return(1);
   };
   len = (sb.st_size * 2);

   // allocates memory
   if (!(buff = malloc(len)))
   {
      fprintf(stderr, "peminfo: out of virtual memory\n");
      return(1);
   };

   // opens file for reading
   if ((fd = open(argv[1], O_RDONLY)) == -1)
   {
      perror("peminfo: open()");
      free(buff);
      return(1);
   };

   // reads file
   if ((len = read(fd, buff, len)) == -1)
   {
      perror("peminfo: read()");
      free(buff);
      return(1);
   };

   // closes file
   close(fd);

   // initialize OpenSSL
   SSL_load_error_strings();
   SSL_library_init();

   // creates BIO buffer
   bio = BIO_new_mem_buf(buff, len);

   // decodes buffer
   if (!(x = PEM_read_bio_X509(bio, NULL, 0L, NULL)))
   {
      while((err = ERR_get_error()))
      {
         errmsg[1023] = '\0';
         ERR_error_string_n(err, errmsg, 1023);
         fprintf(stderr, "peminfo: %s\n", errmsg);
      };
      BIO_free(bio);
      free(buff);
      return(1);
   };

   // prints x509 info
   printf("name:      %s\n",    x->name);
   printf("serial:    ");
   printf("%02X", x->cert_info->serialNumber->data[0]);
   for(pos = 1; pos < x->cert_info->serialNumber->length; pos++)
      printf(":%02X", x->cert_info->serialNumber->data[pos]);
   printf("\n");

   // calculate & print fingerprint
   digest = EVP_get_digestbyname("sha1");
   X509_digest(x, digest, md, &n);
   printf("Fingerprint: ");
   for(pos = 0; pos < 19; pos++)
      printf("%02x:", md[pos]);
   printf("%02x\n", md[19]);

   // frees memory
   BIO_free(bio);
   free(buff);

   return(0);
}
 
 
 ---------------------------------------------

Here is the compiling and output of the above program:

$ cc -pedantic -W -Wall -Werror -O2  -Wno-deprecated -o peminfo  peminfo.c \
> -lcrypto -lssl
$ ./peminfo /usr/local/etc/openldap/keys/ca-certs.pem 
 
serial:      98:61:EB:C4:F2:C9:59:72
Fingerprint: 1d:59:d3:d4:4f:c9:e3:dc:f3:d7:66:b0:b8:7e:87:0b:01:73:c2:7e
 
 ---------------------------------------------
 
Here is the output from the openssl utility:

$ openssl x509 -noout -in /usr/local/etc/openldap/keys/ca-certs.pem \
> -fingerprint -serial
 
SHA1 Fingerprint=1D:59:D3:D4:4F:C9:E3:DC:F3:D7:66:B0:B8:7E:87:0B:01:73:C2:7E
serial=9861EBC4F2C95972
 
 ---------------------------------------------

 */





























