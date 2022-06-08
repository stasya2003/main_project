#pragma once
#include <iostream>

namespace mt::math
{
	

	template<typename T, int N, int M>
	struct MasWrapper
	{
		T mas[N][M];
	};

	template<typename T, int N, int M>
	class Matrix
	{
	public:

		int getN() const { return m_n; }
		int getM() const { return m_m; }
		T get(int i, int j) const { return m_mat[i][j]; }
		void set(int i, int j, T data) { m_mat[i][j] = data; }

		// Constructor
		Matrix()
		{
#ifdef DEBUG
			std::cout << "Constructor" << std::endl;
#endif
			m_n = N;
			m_m = M;
			for (int i = 0; i < m_n; i++)
				for (int j = 0; j < m_m; j++)
					m_mat[i][j] = 0;
		}

		Matrix(const T mas[N][M])
		{
#ifdef MY_DEBUG
			std::cout << "Constructor" << std::endl;
#endif
			m_n = N;
			m_m = M;
			for (int i = 0; i < m_n; i++)
				for (int j = 0; j < m_m; j++)
					m_mat[i][j] = mas[i][j];
		}

		Matrix(const MasWrapper<T, N, M>& mas)
		{
#ifdef MY_DEBUG
			std::cout << "Constructor" << std::endl;
#endif
			m_n = N;
			m_m = M;
			for (int i = 0; i < m_n; i++)
				for (int j = 0; j < m_m; j++)
					m_mat[i][j] = mas.mas[i][j];
		}

		//Copy constructor
		Matrix(const Matrix<T, N, M>& mat)
		{
#ifdef DEBUG
			std::cout << "Copy constructor" << std::endl;
#endif

			m_n = mat.getN();
			m_m = mat.getM();

			for (int i = 0; i < m_n; i++)
				for (int j = 0; j < m_m; j++)
					m_mat[i][j] = mat.get(i, j);
		}

		// Assignment
		template<typename T, int N, int M>
		Matrix<T, N, M>& operator=(const Matrix<T, N, M>& mat)
		{
			if ((m_n == mat.getN()) && (m_m == mat.getM()))
			{
#ifdef DEBUG
				std::cout << "Operator =" << std::endl;
#endif
				m_n = mat.getN();
				m_m = mat.getM();

				for (int i = 0; i < m_n; i++)
					for (int j = 0; j < m_m; j++)
						m_mat[i][j] = mat.get(i, j);
				return *this;
			}
			else
				std::cout << "Incorrect matrix!" << std::endl;
		}

		// Addition operator
		template<typename T, int N, int M>
		Matrix<T, N, M> operator+(const Matrix<T, N, M>& mat)
		{
			if ((m_n == mat.getN()) && (m_m == mat.getM()))
			{
#ifdef DEBUG
				std::cout << "operator+" << std::endl;
#endif
				Matrix<T, N, M> tmp;
				for (int i = 0; i < m_n; i++)
					for (int j = 0; j < m_m; j++)
						tmp.set(i, j, (m_mat[i][j] + mat.get(i, j)));
				return tmp;
			}
			else
				std::cout << "Incorrect matrix!" << std::endl;
		}

		//Subtraction operator
		template<typename T, int N, int M>
		Matrix<T, N, M> operator-(const Matrix<T, N, M>& mat)
		{
			if ((m_n == mat.getN()) && (m_m == mat.getM()))
			{
#ifdef DEBUG
				std::cout << "operator-" << std::endl;
#endif
				Matrix<T, N, M> tmp;
				for (int i = 0; i < m_n; i++)
					for (int j = 0; j < m_m; j++)
						tmp.set(i, j, (m_mat[i][j] - mat.get(i, j)));
				return tmp;
			}
			else
				std::cout << "Incorrect matrix!" << std::endl;
		}

		//Multiplication operator
		template<typename T, int N, int M>
		Matrix<T, N, M> operator*(const Matrix<T, N, M>& mat)
		{
			if (m_m == mat.getN())
			{
#ifdef DEBUG
				std::cout << "operator*" << std::endl;
#endif
				Matrix<T, N, M> tmp;
				for (int i = 0; i < m_n; i++)
					for (int j = 0; j < mat.getM(); j++)
					{
						T sum = 0;
						for (int k = 0; k < m_m; k++)
							sum += m_mat[i][k] * mat.get(k, j);
						tmp.set(i, j, sum);

					}
				return tmp;
			}
			else
				std::cout << "Incorrect matrix!" << std::endl;
		}

		//Determinant
		T Det()
		{
			if (m_n != m_m)
			{
				std::cout << "Operation not available!" << std::endl;
			}

			else if (m_n == m_m)
			{
				if (m_n == 2)  //det 2 order
				{
					T d = 0;
					d = (m_mat[0][0] * m_mat[1][1] - m_mat[0][1] * m_mat[1][0]);
					return d;
				}
				else if (m_n == 3)  //det 3 order
				{
					T d = 0;
					d = (m_mat[0][0] * m_mat[1][1] * m_mat[2][2] + m_mat[1][0] * m_mat[2][1] * m_mat[0][2] + m_mat[0][1] * m_mat[1][2] * m_mat[2][0] - m_mat[0][2] * m_mat[1][1] * m_mat[2][0] - m_mat[1][2] * m_mat[2][1] * m_mat[0][0] - m_mat[0][1] * m_mat[1][0] * m_mat[2][2]);
					return d;
				}
				else
				{
					T d = 1;
					Gauss();
					for (int i = 0; i < m_n; i++)
						for (int j = 0; j < m_m; j++)
						{
							if (i == j)
							{
								d = d * m_mat[i][j];
							}
						}
				}

			}
		}

		//Reverse
		Matrix<double, N, M> Reverse()
		{
			T det = Det();

			if (det == 0)
			{
				std::cout << "Inverse matrix not exist!" << std::endl;
			}
			else if (m_n == m_m)
			{
				Matrix<double, N, M> tmp;

				if (m_n == 2)
				{
					tmp.set(0, 0, m_mat[1][1] / det);
					tmp.set(0, 1, -m_mat[0][1] / det);
					tmp.set(1, 0, -m_mat[1][0] / det);
					tmp.set(1, 1, m_mat[1][1] / det);
					return tmp;
				}
				else if (m_n == 3)
				{
					tmp.set(0, 0, ((m_mat[1][1] * m_mat[2][2] - m_mat[2][1] * m_mat[1][2]) / det));
					tmp.set(1, 0, (-(m_mat[1][0] * m_mat[2][2] - m_mat[2][0] * m_mat[1][2]) / det));
					tmp.set(2, 0, ((m_mat[1][0] * m_mat[2][1] - m_mat[2][0] * m_mat[1][1]) / det));
					tmp.set(0, 1, (-(m_mat[0][1] * m_mat[2][2] - m_mat[2][1] * m_mat[0][2]) / det));
					tmp.set(1, 1, ((m_mat[0][0] * m_mat[2][2] - m_mat[2][0] * m_mat[0][2]) / det));
					tmp.set(2, 1, (-(m_mat[0][0] * m_mat[2][1] - m_mat[2][0] * m_mat[0][1]) / det));
					tmp.set(0, 2, ((m_mat[0][1] * m_mat[1][2] - m_mat[1][1] * m_mat[0][2]) / det));
					tmp.set(1, 2, (-(m_mat[0][0] * m_mat[1][2] - m_mat[1][0] * m_mat[0][2]) / det));
					tmp.set(2, 2, ((m_mat[0][0] * m_mat[1][1] - m_mat[1][0] * m_mat[0][1]) / det));
					return tmp;
				}
			}
		}

		//Transposition
		Matrix<T, M, N> Transp()
		{
			Matrix<T, M, N> tmp;
			for (int i = 0; i < M; i++)
				for (int j = 0; j < N; j++)
				{
					tmp.set(i, j, m_mat[j][i]);
				}
			return tmp;
		}

		//Gauss

		Matrix<T, N, M> Gauss()
		{
			double a = 0;

			for (int i = 0; i < M; i++)
				for (int j = 0; j < N; j++)
				{
					if (i == j)
					{
						for (int r = j + 1; r < N; r++)
						{
							if (r < N)
							{
								if (m_mat[r][i] != 0)
								{
									a = m_mat[r][i] / m_mat[j][i];
									for (int t = i; t < M; t++)
									{
										m_mat[r][t] = m_mat[r][t] - a * m_mat[j][t];
									}
								}
							}
						}
					}
				}
			return *this;   //det
		}


		// Destructor
		~Matrix()
		{
#ifdef DEBUG
			std::cout << "Destructor" << std::endl;
#endif
		}


		template<typename T, int N, int M>
		friend std::istream& operator>>(std::istream& os, Matrix<T, N, M>& mat);
		template<typename T, int N, int M>
		friend std::ostream& operator<<(std::ostream& os, const Matrix<T, N, M>& mat);


	private:
		int m_n, m_m;
		T m_mat[N][M];
	};

	template<typename T, int N, int M>
	std::istream& operator>>(std::istream& in, Matrix<T, N, M>& mat)
	{
		for (int i = 0; i < mat.m_n; i++)
			for (int j = 0; j < mat.m_m; j++)
				in >> mat.m_mat[i][j];
		return in;

	}

	template<typename T, int N, int M>
	std::ostream& operator<<(std::ostream& out, const Matrix<T, N, M>& mat)
	{
		out << "Matrix " << mat.m_n << "x" << mat.m_m << std::endl;
		for (int i = 0; i < mat.m_n; i++) {
			for (int j = 0; j < mat.m_m; j++)
				out << mat.m_mat[i][j] << " ";
			out << std::endl;
		}
		return out;
	}

	using Vec21i = Matrix<int, 2, 1>;
	using Vec31i = Matrix<int, 3, 1>;
	using Vec12i = Matrix<int, 1, 2>;
	using Vec21d = Matrix<double, 2, 1>;
	using Vec31d = Matrix<double, 3, 1>;
	using Vec13d = Matrix<double, 1, 3>;
	using Vec12d = Matrix<double, 1, 2>;

	using Mat22i = Matrix<int, 2, 2>;
	using Mat23i = Matrix<int, 2, 3>;
	using Mat22d = Matrix<double, 2, 2>;
	using Mat33d = Matrix<double, 3, 3>;
	using Mat44d = Matrix<double, 4, 4>;

	using Mat23d = Matrix<double, 2, 3>;
	using Mat34d = Matrix<double, 3, 4>;
	using Mat45d = Matrix<double, 4, 5>;
	using Mat56d = Matrix<double, 5, 6>;
	using Mat67d = Matrix<double, 6, 7>;
	using Mat78d = Matrix<double, 7, 8>;
	using Mat89d = Matrix<double, 8, 9>;
	using Mat910d = Matrix<double, 9, 10>;
	using Mat1011d = Matrix<double, 10, 11>;

}