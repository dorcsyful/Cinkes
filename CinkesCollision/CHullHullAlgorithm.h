#pragma once
class CHullHullAlgorithm
{
public:
	CHullHullAlgorithm() = default;
	~CHullHullAlgorithm() = default;

	CHullHullAlgorithm(const CHullHullAlgorithm& a_Rhs) = delete;
	CHullHullAlgorithm(CHullHullAlgorithm&& a_Rhs) noexcept = delete;
	//}

	//Subgroup: Operators {
	CHullHullAlgorithm& operator=(CHullHullAlgorithm&& a_Rhs) noexcept = delete;
	CHullHullAlgorithm& operator=(const CHullHullAlgorithm& a_Rhs) noexcept = delete;
};

