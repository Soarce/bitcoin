// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2013 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"

#include "assert.h"
#include "core.h"
#include "protocol.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

//
// Main network
//

unsigned int pnSeed[] =
{
    0x42b91f24 // games.soarcetech.com
};

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x86; //86 => †
        pchMessageStart[1] = 0xe4; //e4 => ä
        pchMessageStart[2] = 0x86; //86 => †
        pchMessageStart[3] = 0xae; //ae => ®
        vAlertPubKey = ParseHex("04fc9702847840aaf195de8442ebecedf5b095cdbb9bc716bda9110971b28a49e0ead8564ff0db22209e0374782c093bb899692d524e9d6a6956e7c5ecbcd68284");
        nDefaultPort = 57473;
        nRPCPort = 47472;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 32);
        nSubsidyHalvingInterval = 210000;

        // Build the genesis block. Note that the output of the genesis coinbase cannot
        // be spent as it did not originally exist in the database.
        //
        const char* pszTimestamp = "Anatol Rapoport-1980 Being 'nice' can be beneficial, but it can also lead to being suckered";
        CTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CBigNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 50 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04855b332d7ab6fcabce6b7282c6d447db25e77b3fb705f497bd673f3c47fcbf6f2968623bb4047f0d8b59aa1e5cc0a9fff8315f7d46c75c4d1671ebb6cb27bf46") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 315532800;
        genesis.nBits    = 0x1d00ffff;
        genesis.nNonce   = 2214851013;
        //genesis.print();

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x0000000013d1dfc64b8f226c1551079ea0b353a89b3f76b050a2487a068cf15a"));
        assert(genesis.hashMerkleRoot == uint256("0x1d5313d9a8bde3d5eabf473cba67a1851a1c160fa9d3bb95ff7b18c5de11eae9"));

//        vSeeds.push_back(CDNSSeedData("bitcoin.sipa.be", "seed.bitcoin.sipa.be"));
//        vSeeds.push_back(CDNSSeedData("bluematt.me", "dnsseed.bluematt.me"));
//        vSeeds.push_back(CDNSSeedData("dashjr.org", "dnsseed.bitcoin.dashjr.org"));
//        vSeeds.push_back(CDNSSeedData("bitcoinstats.com", "seed.bitcoinstats.com"));
//        vSeeds.push_back(CDNSSeedData("xf2.org", "bitseed.xf2.org"));
        vSeeds.push_back(CDNSSeedData("soarcetech.com", "seed.tatcoin.soarcetech.com"));

        base58Prefixes[PUBKEY_ADDRESS] = list_of(65);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(68);
        base58Prefixes[SECRET_KEY] =     list_of(70);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x8a)(0xB4)(0x20);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x8a)(0xAF)(0xE6);

        // Convert the pnSeeds array into usable address objects.
        for (unsigned int i = 0; i < ARRAYLEN(pnSeed); i++)
        {
            // It'll only connect to one or two seed nodes because once it connects,
            // it'll get a pile of addresses with newer timestamps.
            // Seed nodes are given a random 'last seen time' of between one and two
            // weeks ago.
            const int64_t nOneWeek = 7*24*60*60;
            struct in_addr ip;
            memcpy(&ip, &pnSeed[i], sizeof(ip));
            CAddress addr(CService(ip, GetDefaultPort()));
            addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
            vFixedSeeds.push_back(addr);
        }
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
// Testnet (v3)
//
class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x83; //83 => ƒ
        pchMessageStart[1] = 0xe2; //e4 => â
        pchMessageStart[2] = 0xae; //86 => ®
        pchMessageStart[3] = 0x86; //ae => †
        vAlertPubKey = ParseHex("04302390343f91cc401d56d68b123028bf52e5fca1939df127f63c6467cdf9c8e2c14b61104cf817d0b780da337893ecc4aaff1309e536162dabbdb45200ca2b0a");
        nDefaultPort = 57475;
        nRPCPort = 57474;
        strDataDir = "testnet3";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 315532807;
        genesis.nNonce = 20431863;
        // genesis.print();
        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00000000464a6775fade3f46d63538c96e42f0aa311c26c62fdb452c0601558a"));

        vFixedSeeds.clear();
        vSeeds.clear();
//        vSeeds.push_back(CDNSSeedData("bitcoin.petertodd.org", "testnet-seed.bitcoin.petertodd.org"));
//        vSeeds.push_back(CDNSSeedData("bluematt.me", "testnet-seed.bluematt.me"));
        vSeeds.push_back(CDNSSeedData("soarcetech.com", "testnet-seed.tatcoin.soarcetech.com"));

        base58Prefixes[PUBKEY_ADDRESS] = list_of(73);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(75);
        base58Prefixes[SECRET_KEY]     = list_of(78);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x37)(0x89)(0xD1);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x37)(0x85)(0x96);
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        pchMessageStart[0] = 0xde;
        pchMessageStart[1] = 0xad;
        pchMessageStart[2] = 0xbe;
        pchMessageStart[3] = 0xef; // classic
        nSubsidyHalvingInterval = 150;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        genesis.nTime = 1391388473;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 0;
        //genesis.print();
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 57476;
        strDataDir = "regtest";
        assert(hashGenesisBlock == uint256("0x22b0e2b5bbfb9f3b5f2679414777b08879c0e7692f7b5bf93b2841a3e0af10da"));

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.
    }

    virtual bool RequireRPCPassword() const { return false; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};
static CRegTestParams regTestParams;

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
        case CChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest) {
        return false;
    }

    if (fRegTest) {
        SelectParams(CChainParams::REGTEST);
    } else if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
