#include "Random.h"

#include <limits>

std::mt19937												CRandom::m_sRandomEngine;
std::uniform_int_distribution<std::mt19937::result_type>	CRandom::m_sDistribution;

CRandom::CRandom(void)
{
	Seed();
}

CRandom::~CRandom(void)
{

}

void CRandom::Seed(void)
{
	m_sRandomEngine.seed(std::random_device()());
}

uint32_t CRandom::RandomUint(void)
{
	return m_sDistribution(m_sRandomEngine);
}

uint32_t CRandom::RandomUint(const uint32_t Min, const uint32_t Max)
{
	return Min + (RandomUint() % (Max - Min + 1));
}