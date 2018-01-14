// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//
// Main network
//

// Convert the pnSeeds array into usable address objects.
static void convertSeeds(std::vector<CAddress> &vSeedsOut, const unsigned int *data, unsigned int count, int port)
{
     // It'll only connect to one or two seed nodes because once it connects,
     // it'll get a pile of addresses with newer timestamps.
     // Seed nodes are given a random 'last seen time' of between one and two
     // weeks ago.
     const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int k = 0; k < count; ++k)
    {
        struct in_addr ip;
        unsigned int i = data[k], t;
        
        // -- convert to big endian
        t =   (i & 0x000000ff) << 24u
            | (i & 0x0000ff00) << 8u
            | (i & 0x00ff0000) >> 8u
            | (i & 0xff000000) >> 24u;
        
        memcpy(&ip, &t, sizeof(ip));
        
        CAddress addr(CService(ip, port));
        addr.nTime = GetTime()-GetRand(nOneWeek)-nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xd3;
        pchMessageStart[1] = 0x1f;
        pchMessageStart[2] = 0x3d;
        pchMessageStart[3] = 0x05;
        vAlertPubKey = ParseHex("04aef1ba691cf0ab79ce776a69fc0f7427f62ff2a1138928008741a0b6f616ef7d41ae59d6e69ca0a0d21d4909ae5726a7ea5803a572a2e96f9d2268e14a0d702b");
        nDefaultPort = 33290;
        nRPCPort = 33291;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);

        const char* pszTimestamp = "12/Jan/2018 - How Blockchain is Banking the Unbanked";
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, 1515777783, vin, vout, 0);
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1515777783;
        genesis.nBits    = 0x1f00ffff; 
        genesis.nNonce   = 221513;

        hashGenesisBlock = genesis.GetHash();

        assert(hashGenesisBlock == uint256("0x0000429fae9f954dc9a2e25619e287ad19a173e7c2fd242041b12ecc48ee1984"));
        assert(genesis.hashMerkleRoot == uint256("0x7c61ae38dc4c7cefcd40fe19654d7c98364a51f36fef8e5f54cf9b91853bafea"));
                
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,32);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,85);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,153);
        base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1,40);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        vSeeds.push_back(CDNSSeedData("1","s0.digimoney.info"));
        vSeeds.push_back(CDNSSeedData("2","s1.digimoney.info"));
        vSeeds.push_back(CDNSSeedData("3","s2.digimoney.info"));
        vSeeds.push_back(CDNSSeedData("4","s3.digimoney.info"));
        vSeeds.push_back(CDNSSeedData("5","s4.digimoney.info"));
        vSeeds.push_back(CDNSSeedData("6","s5.digimoney.info"));

        convertSeeds(vFixedSeeds, pnSeed, ARRAYLEN(pnSeed), nDefaultPort);

        nPoolMaxTransactions = 3;
        strDarksendPoolDummyAddress = "EFNPNhsofpBNzGtkWiRjbPCZMJAcyA4qVk";
        nLastPOWBlock = 48000;
        nPOSStartBlock = 101;
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xd2;
        pchMessageStart[1] = 0x14;
        pchMessageStart[2] = 0xc8;
        pchMessageStart[3] = 0x13;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        vAlertPubKey = ParseHex("042b2e5e94596c21d8cff4c4568ce53cc60907d52d6b99f62f35e0fedebe9bafff280c8462091b59ee2f69b860b44d264a25f386c10e5630c087ce70cf8246ff1c");
        nDefaultPort = 43290;
        nRPCPort = 43291;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits  = 0x1f00ffff; 
        genesis.nNonce = 221513;

        assert(hashGenesisBlock == uint256("0x0000429fae9f954dc9a2e25619e287ad19a173e7c2fd242041b12ecc48ee1984"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,214);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,206);
        base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1,218);
        base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1,65);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

        convertSeeds(vFixedSeeds, pnTestnetSeed, ARRAYLEN(pnTestnetSeed), nDefaultPort);

        nLastPOWBlock = 0x7fffffff;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    
    bool fTestNet = GetBoolArg("-testnet", false);
    
    if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
