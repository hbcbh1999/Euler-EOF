#include <iostream>
#include <cmath>
#include <vector>

std::vector<double> RoeSolver(std::vector<double> U_L, std::vector<double> U_R, std::vector<double> F_L, std::vector<double> F_R, double gamma)
{

// This function treat Riemann problem on x, y, z direction by changing the sequency of the varible in the outside input. When calculate flux G on y direction, we pass U = [rho, v, u, E] from outside but assign in the function as [rho, u, v, E].  
	std::vector<double> F_interface;
	if ( U_L.size() == 4)
	{
		// TODO: assert the length of the vector to be 4

		// Assign value from left and right state varible
		double rho_L,rho_R,u_L,u_R,v_L,v_R,p_L,p_R,V_L,V_R,E_L,E_R,H_L,H_R;

		rho_L = U_L[0];
		u_L = U_L[1]/rho_L;
		v_L = U_L[2]/rho_L;
		E_L = U_L[3];

		V_L = sqrt(pow(u_L,2) + pow(v_L,2) );
		p_L = (gamma - 1) * (E_L - 0.5 * rho_L * pow(V_L, 2));
		H_L = (E_L + p_L)/rho_L;

		rho_R = U_R[0];
		u_R = U_R[1]/rho_R;
		v_R = U_R[2]/rho_R;
		E_R = U_R[3];

		V_R = sqrt(pow(u_R,2) + pow(v_R,2) );
		p_R = (gamma - 1) * (E_R - 0.5 * rho_R * pow(V_R, 2));
		H_R = (E_R + p_R)/rho_R;

		// // Evaluate Roe average

		double u_m,v_m,H_m,a_m;

		u_m = (sqrt(rho_L)*u_L+sqrt(rho_R)*u_R)/(sqrt(rho_L)+sqrt(rho_R));
		v_m = (sqrt(rho_L)*v_L+sqrt(rho_R)*v_R)/(sqrt(rho_L)+sqrt(rho_R));
		H_m = (sqrt(rho_L)*H_L+sqrt(rho_R)*H_R)/(sqrt(rho_L)+sqrt(rho_R));
		a_m = sqrt ( ( gamma-1 )*( H_m - 1/2 * (pow(u_m,2) + pow(v_m,2) )) );

		// Evaluate eigenvalue of Jacobian matrix

		double lambda[4];

		lambda[0] = u_m - a_m;
		lambda[1] = u_m;
		lambda[2] = u_m;
		lambda[3] = u_m + a_m;

		// Evaluate eigenvector
		double K[4][4] = 
		{
			{1, lambda[0], v_m, H_m - u_m * a_m} ,
			{1, u_m      , v_m, 0.5 * (pow(u_m,2) + pow(v_m,2))},
			{0, 0		 , 1  , v_m},
			{1, lambda[3], v_m, H_m + u_m * a_m}
		};

		// Solve the wave strength from the jump of the state deltaU

		double deltaU[4],alpha[4];

		for (int i=0; i<4; i++)
		{
			deltaU[i] = U_R[i]-U_L[i];
		}

		alpha[1] = (gamma-1)/pow(a_m,2)*(deltaU[0]*(H_m-pow(u_m,2))-u_m*deltaU[1]-(deltaU[3]-(deltaU[2]-v_m*deltaU[0])*v_m));
		alpha[0] = 1/(2*a_m)*(deltaU[0]*(u_m+a_m)-deltaU[1]-a_m*alpha[1]);
		alpha[3] = deltaU[0] - (alpha[0]+alpha[1]);
		alpha[2] = deltaU[2] - v_m * deltaU[0];

		// Compute the flux
		double SumAlphaLambdaK;
		for (int j = 0; j<4; j++)
		{
			SumAlphaLambdaK = 0.0;
			for (int i=0; i<4; i++)
			{
				SumAlphaLambdaK = SumAlphaLambdaK + alpha[i]* std::abs(lambda[i])*K[i][j];
			}
			double result = 0.5*(F_L[j]+F_R[j]) - 0.5 * SumAlphaLambdaK;
			F_interface.push_back(result);
		}	  
	}
	else
	{
		// TODO: 3D case
	}

	return F_interface;
}
