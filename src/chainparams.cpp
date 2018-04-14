// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2017 The Dash developers
// Copyright (c) 2017-2018 The BitNodesPro developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"

#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

static Checkpoints::MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
        (  0, uint256("0x00000281c9b573da3042ebcd6784369a55674e58b4bc222cef90815d75b54c2b"))
        ;
static const Checkpoints::CCheckpointData data = {
        &mapCheckpoints, 1516946400, 0, 2800
    };

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
        boost::assign::map_list_of
        ( 0, uint256("0x000005792f3627994a810db8ec6ce9127c16ecf59f5a9af888ad4fcf64b6c984"))
        ;
static const Checkpoints::CCheckpointData dataTestnet = {
        &mapCheckpointsTestnet, 1519884000, 0, 500
    };

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
        boost::assign::map_list_of
        ( 0, uint256("0x0d1c71a9390886bbbb69d9a1c24e2cfa01a23be0f63553403aba5432184ca8c9"))
        ;
static const Checkpoints::CCheckpointData dataRegtest = {
        &mapCheckpointsRegtest, 0, 0, 0
    };

class CMainParams : public CChainParams {
public:
    CMainParams() {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";

        pchMessageStart[0] = 0xf9;
        pchMessageStart[1] = 0xfe;
        pchMessageStart[2] = 0x6b;
        pchMessageStart[3] = 0xbd;
        vAlertPubKey = ParseHex("042129cdbe7ba51e95fafc201c286a08f0ca5dde345cfbfcd6f7513c9d006cd6e1470de7855672547978d7fa27d9d14bd2808feb923d91bdd73b37373e6f6b417a");
        nDefaultPort = 2632;
        bnProofOfWorkLimit = ~uint256(0) >> 20;  // BitNodesPro starting difficulty is 1 / 2^12
        nSubsidyHalvingInterval = 262800;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 24 * 60 * 60; // BitNodesPro: 1 day
        nTargetSpacing = 2 * 60; // BitNodesPro: 2 minutes


        const char* pszTimestamp = "1998 Intel launches 333 MHz Pentium II chip";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 50 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04e5329e7170dc698e5960ac470ff1b4731c3650b452d29748223fd931aeed8d116b808ffdbeaba7813c4e63fffb4eeee88ea4d5c119083debb47e5c5003293128") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        
        genesis.nTime    = 1516946400;
        genesis.nBits    = 0x1e0ffff0;
        genesis.nNonce   = 2073493;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00000281c9b573da3042ebcd6784369a55674e58b4bc222cef90815d75b54c2b"));
        assert(genesis.hashMerkleRoot == uint256("0xab182f4f121dd0986e60d73e95d87b6867d954113403ca0e708485c250744b1a"));

        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = list_of(53);                     // BitNodesPro addresses start with 'N'
        base58Prefixes[SCRIPT_ADDRESS] = list_of(0);                      // BitNodesPro script addresses start with '1'
        base58Prefixes[SECRET_KEY]     = list_of(128);                    // BitNodesPro private keys start with '5'
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E); // BitNodesPro BIP32 pubkeys start with 'xpub'
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4); // BitNodesPro BIP32 prvkeys start with 'xprv'
        base58Prefixes[EXT_COIN_TYPE]  = list_of(0x8000002D);             // BitNodesPro BIP44 coin type is '45'

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;

        nPoolMaxTransactions = 3;
        strMasternodePaymentsPubKey = "04949830c1771a1d25896b2d3d7c7cca006cbd6ba1395ed0b946780ba30e9589b49ab9bab71a1f24799b8b307670044ac395759bf86d5402ca908a34415e6bc9fd";
        strDarksendPoolDummyAddress = "NeSgnf9Us5mQU56jwDfEv4B4C6wBANfADM";
        nStartMasternodePayments = 1516946410;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const 
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0xce;
        pchMessageStart[1] = 0xfa;
        pchMessageStart[2] = 0xca;
        pchMessageStart[3] = 0xff;
        vAlertPubKey = ParseHex("04458eba965d637715d00bf146d2295b6c421094a9d48d466783bf235d8010f95e0c2073d6c09bec4c27ecd9c845640fed3b8100f1ba13678925d67cd8273a52f5");
        nDefaultPort = 17732;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 24 * 60 * 60; // BitNodesPro: 1 day
        nTargetSpacing = 2 * 60; // BitNodesPro: 2 minutes

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1519884000;
        genesis.nNonce = 2508864;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x000005792f3627994a810db8ec6ce9127c16ecf59f5a9af888ad4fcf64b6c984"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = list_of(53);                     // Testnet BitNodesPro addresses start with 'N'
        base58Prefixes[SCRIPT_ADDRESS] = list_of(0);                      // Testnet BitNodesPro script addresses start with '1'
        base58Prefixes[SECRET_KEY]     = list_of(128);                    // Testnet BitNodesPro private keys start with '5'
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF); // Testnet BitNodesPro BIP32 pubkeys start with 'tpub'
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94); // Testnet BitNodesPro BIP32 prvkeys start with 'tprv'
        base58Prefixes[EXT_COIN_TYPE]  = list_of(0x80000001);             // Testnet BitNodesPro BIP44 coin type is '1'

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strMasternodePaymentsPubKey = "0457eb13ba1a084d5f831942b819b557e0669e441621cad65b7e167d8f209ec5fafd7c74786144df61582bcce043f54310410206e95078c33f2d59369af93404ea";
        strDarksendPoolDummyAddress = "NeSnpf9Us5mQU14jwYfEG4B4C6wmANfADM";
        nStartMasternodePayments = 1519884010;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const 
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        pchMessageStart[0] = 0xfc;
        pchMessageStart[1] = 0xc1;
        pchMessageStart[2] = 0xb7;
        pchMessageStart[3] = 0xdc;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // BitNodesPro: 1 day
        nTargetSpacing = 2 * 60; // BitNodesPro: 2 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1522562400;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 0;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 17632;
        assert(hashGenesisBlock == uint256("0x133bc314fe3cf702f19b16c7f74ec7935412d9d440c9492f6d0e1287e83d4131"));

        vFixedSeeds.clear(); //! Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();  //! Regtest mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const 
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams {
public:
    CUnitTestParams() {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 18334;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();  //! Unit test mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const 
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval)  { nSubsidyHalvingInterval=anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority)  { nEnforceBlockUpgradeMajority=anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority)  { nRejectBlockOutdatedMajority=anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority)  { nToCheckBlockUpgradeMajority=anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks)  { fDefaultConsistencyChecks=afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) {  fAllowMinDifficultyBlocks=afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams *pCurrentParams = 0;

CModifiableParams *ModifiableParams()
{
   assert(pCurrentParams);
   assert(pCurrentParams==&unitTestParams);
   return (CModifiableParams*)&unitTestParams;
}

const CChainParams &Params() {
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams &Params(CBaseChainParams::Network network) {
    switch (network) {
        case CBaseChainParams::MAIN:
            return mainParams;
        case CBaseChainParams::TESTNET:
            return testNetParams;
        case CBaseChainParams::REGTEST:
            return regTestParams;
        case CBaseChainParams::UNITTEST:
            return unitTestParams;
        default:
            assert(false && "Unimplemented network");
            return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network) {
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
