#pragma once


#include "Circuit/Gate.h"
#include "Common/Defines.h"
#include <array>
#include  "Common/ArrayView.h"

namespace osuCrypto
{

	typedef u32 BetaWire;
	struct BetaGate
	{
		BetaGate(const BetaWire& in0, const BetaWire& in1, const GateType& gt, const BetaWire& out)
			: mInput({in0, in1})
			, mOutput(out)
			, mType(gt)
			, mAAlpha(gt == GateType::Nor || gt == GateType::na_And || gt == GateType::nb_Or || gt == GateType::Or)
			, mBAlpha(gt == GateType::Nor || gt == GateType::nb_And || gt == GateType::na_Or || gt == GateType::Or)
			, mCAlpha(gt == GateType::Nand || gt == GateType::nb_Or || gt == GateType::na_Or || gt == GateType::Or)
		{}

		std::array<BetaWire, 2> mInput;
		BetaWire mOutput;
		GateType mType;
		u8 mAAlpha, mBAlpha, mCAlpha;
	};


	struct BetaLevel
	{
		std::vector<BetaGate> mXorGates, mAndGates;
	};

	static_assert(sizeof(GateType) == 1, "");
	static_assert(sizeof(BetaGate) == 16, "");
	
	struct BetaBundle
	{
        BetaBundle() {}
		BetaBundle(u64 s) :mWires(s) {}
		std::vector<BetaWire> mWires;
	};


	class BetaCircuit
	{
	public:
		BetaCircuit();
		~BetaCircuit();



		u64 mNonXorGateCount;
        BetaWire mWireCount;
        std::vector<BetaGate> mGates;
        std::vector<std::tuple<u64, BetaWire, std::string>> mPrints;
		std::vector<BetaLevel> mLevelGates;

		void addTempWireBundle(BetaBundle& in);
		void addInputBundle(BetaBundle& in);
		void addOutputBundle(BetaBundle& in);
		void addGate(BetaWire in0, BetaWire in2, GateType gt, BetaWire out);

        void addPrint(BetaBundle in);
        void addPrint(BetaWire wire);
        void addPrint(std::string);

        std::vector<BetaBundle> mInputs, mOutputs;
        
        void evaluate(ArrayView<BitVector> input, ArrayView<BitVector> output, bool print = true);

		void levelize();
	};

}