// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2017 The Dash developers
// Copyright (c) 2017 The BitNodes developers
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
        (  0, uint256("0x0000086bc1314567c516c7a39573968880d1a754e36f3c69deba80c641d7b219"))
        ;
static const Checkpoints::CCheckpointData data = {
        &mapCheckpoints, 1514278800, 0, 2800
    };

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
        boost::assign::map_list_of
        ( 0, uint256("0x000007504bdfef474b55203dd990645408eb0a9a3c4ba222570dfdd656819fde"))
        ;
static const Checkpoints::CCheckpointData dataTestnet = {
        &mapCheckpointsTestnet, 1517443200, 0, 500
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
        vAlertPubKey = ParseHex("0466b6916465661ad39d2bc298058b9229fc34e50b87532bbf580c282bcba78b2e8b8d99897121e2fef51c2274bb57fffc172fab75171d2ca82c91feaf60efe1e0");
        nDefaultPort = 7227;
        bnProofOfWorkLimit = ~uint256(0) >> 20;  // BitNodes starting difficulty is 1 / 2^12
        nSubsidyHalvingInterval = 21600;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 24 * 60 * 60; // BitNodes: 1 day
        nTargetSpacing = 2 * 60; // BitNodes: 2 minutes


        const char* pszTimestamp = "The Beatles. I Want to Hold Your Hand 12/26/2017@9/00am UTC";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 50 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("040f084712e3c7cb08a5086e49ef8627c801f1e2d42325a4a0274f98bca6d4a773769c8f1d4c9e1f993f7ad4d75aa2fc24b72a6365715b88746b8f41870e4ca192") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        
        genesis.nTime    = 1514278800;
        genesis.nBits    = 0x1e0ffff0;
        genesis.nNonce   = 117134;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x0000086bc1314567c516c7a39573968880d1a754e36f3c69deba80c641d7b219"));
        assert(genesis.hashMerkleRoot == uint256("0xf6df48aafc6ff3f80098859550903dccd85a301c7b77eaac5a4dc3f498383496"));

        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = list_of(53);                     // BitNodes addresses start with 'N'
        base58Prefixes[SCRIPT_ADDRESS] = list_of(0);                      // BitNodes script addresses start with '1'
        base58Prefixes[SECRET_KEY]     = list_of(128);                    // BitNodes private keys start with '5'
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E); // BitNodes BIP32 pubkeys start with 'xpub'
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4); // BitNodes BIP32 prvkeys start with 'xprv'
        base58Prefixes[EXT_COIN_TYPE]  = list_of(0x8000002D);             // BitNodes BIP44 coin type is '45'

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
        strMasternodePaymentsPubKey = "0473c8707ed03770b71285829c7a0b944ba700f85deb6dae95b5aa32a29501fd5d9368ca112f93cfefd5ffaccf3d09d1ebbac95ad6e16d5239c129ac2d9c7e7dd6";
        strDarksendPoolDummyAddress = "NeSnpf9Us5mQU56jwYYEv4B4C6wBANfADM";
        nStartMasternodePayments = 1514278805;
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
        vAlertPubKey = ParseHex("04faa632781a7673b5c7057419bbf5263d474663cbc28f37682d6775f5d4e56d05ce68e5b385a57b042e5a02b15bba922c3e7217ebf199e0583ac3760b444243ba");
        nDefaultPort = 17779;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 24 * 60 * 60; // BitNodes: 1 day
        nTargetSpacing = 2 * 60; // BitNodes: 2 minutes

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1517443200;
        genesis.nNonce = 164898;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x000007504bdfef474b55203dd990645408eb0a9a3c4ba222570dfdd656819fde"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = list_of(53);                     // Testnet BitNodes addresses start with 'N'
        base58Prefixes[SCRIPT_ADDRESS] = list_of(0);                      // Testnet BitNodes script addresses start with '1'
        base58Prefixes[SECRET_KEY]     = list_of(128);                    // Testnet BitNodes private keys start with '5'
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF); // Testnet BitNodes BIP32 pubkeys start with 'tpub'
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94); // Testnet BitNodes BIP32 prvkeys start with 'tprv'
        base58Prefixes[EXT_COIN_TYPE]  = list_of(0x80000001);             // Testnet BitNodes BIP44 coin type is '1'

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strMasternodePaymentsPubKey = "04c4a98bce03576020950581d749cda942d3ea23ae443095d8f1d6cd28166d5d4415415a7a61c0d57b10e841e28254a92446162c3a783069f1c719f40693e8df56";
        strDarksendPoolDummyAddress = "NeSnpf9Us5mQU56jwYYEv4B4C6wBANfADM";
        nStartMasternodePayments = 1514278800;
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
        nTargetTimespan = 24 * 60 * 60; // BitNodes: 1 day
        nTargetSpacing = 2 * 60; // BitNodes: 2 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1518566400;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 1;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 17774;
        assert(hashGenesisBlock == uint256("0x739b1fa116eb3952141850e937526fcb4951da3bd9dcf3d34d1d9e87bcd3096b"));

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
