#include "network.h"
#include "random.h"

using namespace std;


void Network::resize(const size_t& news) {
	values.resize(news);
	RNG.normal(values);
}

bool Network::add_link(const size_t& one, const size_t& two) {
	vector<size_t>linked=neighbors(one);
	for(auto s:linked) {
		if (s==two) {
			return false;
		}
	}
	vector<size_t>linkedtwo=neighbors(two);
	for(auto sec:linkedtwo) {
		if (sec==one) {
			return false;
		}
	}
	if(one==two or one>=size() or two>=size()) {
		return false;
	} else {
    links.insert({one, two});
    links.insert({two, one});
    return true;
	}
}

size_t Network::random_connect(const double& mean_deg) {
	size_t tot_link = 0; 
	links.erase(links.begin(), links.end());
	
	vector<size_t> nu;
	
	for (size_t i=0; i<size(); ++i) {
		nu.push_back(i);
		}
		
	 for (size_t cen(0); cen < size(); ++cen) {
		 size_t numb(RNG.poisson(mean_deg));
		 
		 if (numb>size()) {
			 numb=size();
		 }
		 
		 RNG.shuffle(nu);
		 
		 for (size_t i=0; i<numb; ++i){
 		 if(add_link(nu[i], cen)) ++tot_link;
		}
  }
  return tot_link;
}

size_t Network::set_values(const std::vector<double>& ve) {
	size_t amount;
	if (ve.size()>size()) {
		amount=size();
	} else {
		amount=ve.size();
	}
	for(size_t i=0; i<amount; ++i) {
			values[i]=ve[i];
	}
	return amount;
}


size_t Network::size() const {
	return values.size();
}

size_t Network::degree(const size_t &_n) const {
	size_t connections=0;
	auto co = links.equal_range(_n);
	for(auto s=co.first; s!=co.second; ++s) {
		++connections;
	}
	return connections;
}


double Network::value(const size_t &_n) const {	
	return values[_n];
}

vector<double> Network::sorted_values() const {
	auto values2 = values;
	sort(values2.begin(), values2.end());
	reverse(values2.begin(), values2.end());
	return values2;
}

vector<size_t> Network::neighbors(const size_t& nb) const {
	vector<size_t> neigbrs;
	auto re =links.equal_range(nb);
	for(auto s=re.first; s!=re.second; ++s) {
			neigbrs.push_back(s->second);
	}
	return neigbrs;
}

