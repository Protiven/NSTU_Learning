#include "basis.h"

namespace basis
{
	Basis::Basis()
	{
		array <function<double(double)>, nFunc1D> phi_;
		phi_[0] = [](double ksi) { return 1 - ksi; };
		phi_[1] = [](double ksi) { return ksi; };

		array <function<double(double)>, nFunc1D> dphi_ksi;
		dphi_ksi[0] = [](double ksi) { return -1; };
		dphi_ksi[1] = [](double ksi) { return 1; };

		phi[0] = [phi_](double ksi, double etta) { return phi_[0](ksi) * phi_[0](etta); };
		phi[1] = [phi_](double ksi, double etta) { return phi_[1](ksi) * phi_[0](etta); };
		phi[2] = [phi_](double ksi, double etta) { return phi_[0](ksi) * phi_[1](etta); };
		phi[3] = [phi_](double ksi, double etta) { return phi_[1](ksi) * phi_[1](etta); };

		dphiksi[0] = [phi_, dphi_ksi](double ksi, double etta) { return dphi_ksi[0](ksi) * phi_[0](etta); };
		dphiksi[1] = [phi_, dphi_ksi](double ksi, double etta) { return dphi_ksi[1](ksi) * phi_[0](etta); };
		dphiksi[2] = [phi_, dphi_ksi](double ksi, double etta) { return dphi_ksi[0](ksi) * phi_[1](etta); };
		dphiksi[3] = [phi_, dphi_ksi](double ksi, double etta) { return dphi_ksi[1](ksi) * phi_[1](etta); };

		dphietta[0] = [phi_, dphi_ksi](double ksi, double etta) { return phi_[0](ksi) * dphi_ksi[0](etta); };
		dphietta[1] = [phi_, dphi_ksi](double ksi, double etta) { return phi_[1](ksi) * dphi_ksi[0](etta); };
		dphietta[2] = [phi_, dphi_ksi](double ksi, double etta) { return phi_[0](ksi) * dphi_ksi[1](etta); };
		dphietta[3] = [phi_, dphi_ksi](double ksi, double etta) { return phi_[1](ksi) * dphi_ksi[1](etta); };
	}
}
