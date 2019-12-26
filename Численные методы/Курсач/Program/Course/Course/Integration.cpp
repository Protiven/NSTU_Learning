#include "integration.h"

namespace integration
{
	GaussIntegration::GaussIntegration()
	{
		double tmp_gauss_points[2][n_ip] =
		{
			{ 0.0, 0.0, 0.0, sqrt(3.0 / 5.0), -sqrt(3.0 / 5.0), sqrt(3.0 / 5.0), sqrt(3.0 / 5.0), -sqrt(3.0 / 5.0), -sqrt(3.0 / 5.0) },
			{ 0.0, sqrt(3.0 / 5.0), -sqrt(3.0 / 5.0), 0.0, 0.0, sqrt(3.0 / 5.0), -sqrt(3.0 / 5.0), sqrt(3.0 / 5.0), -sqrt(3.0 / 5.0) }
		};
		for (int i = 0; i < 2; i++)
			for (int j = 0; j < n_ip; j++)
				gaussPoints[i][j] = tmp_gauss_points[i][j];

		gaussWeights[0] = 64.0 / 81.0;
		gaussWeights[1] = gaussWeights[2] = gaussWeights[3] = gaussWeights[4] = 40.0 / 81.0;
		gaussWeights[5] = gaussWeights[6] = gaussWeights[7] = gaussWeights[8] = 25.0 / 81.0;

		gaussPoints1[0] = -sqrt(3.0 / 5.0); gaussPoints1[1] = 0.0; gaussPoints1[2] = sqrt(3.0 / 5.0);
		gaussWeights1[0] = 5.0 / 9.0; gaussWeights1[1] = 8.0 / 9.0; gaussWeights1[2] = 5.0 / 9.0;
	}
}
