#pragma once
#include <cstdint>
#include <array>

namespace sugaar {
	template <std::uint64_t N>
	class Vector {
	public:
		Vector<N>() : e() {}
		Vector<N>(std::array<double, N> vals) : e(vals) {}

		template<std::uint64_t N = 2> Vector(double x, double y) : e({ x,y }) {}
		template<std::uint64_t N = 3> Vector(double x, double y, double z) : e({ x,y,z }) {}
		template<std::uint64_t N = 4> Vector(double x, double y, double z, double w) : e({ x,y,z,w }) {}

		double X() const { return e[0]; }
		double Y() const { return e[1]; }
		double Z() const { return e[2]; }
		double W() const { return e[3]; }

		Vector operator-() const {
			std::array<double, N> inverted;
			for (std::uint64_t i = 0; i < N; i++)
				inverted[i] = -e[i];
			return Vector<N>(inverted);
		}

		double operator[](int i) const { return e[i]; }
		double& operator[](int i) { return e[i]; }

		Vector& operator+=(const Vector<N>& v) {
			for (int i = 0; i < N; i++) {
				e[i] += v[i];
			}
			return *this;
		}

		Vector& operator*=(const Vector<N>& v) {
			for (int i = 0; i < N; i++) {
				e[i] *= v[i];
			}
			return *this;
		}

		Vector& operator*=(double lambda) {
			for (int i = 0; i < N; i++) {
				e[i] += lambda;
			}
			return *this;
		}

		Vector& operator/=(double lambda) {
			return *this *= 1 / lambda;
		}

		double length() const {
			return sqrt(length_squared());
		}

		double length_squared() const {
			return (this) * (this);
		}

	private:
		std::array<double, N> e;
	};

	template<std::uint64_t N>
	inline Vector<N> operator+(const Vector<N>& A, const Vector<N>& B) {
		std::array<double, N> Cvals;
		for (int i = 0; i < N; i++) {
			Cvals = A[i] + B[i];
		}
		return Vector<N>(Cvals);
	}

	template<std::uint64_t N>
	inline Vector<N> operator-(const Vector<N>& A, const Vector<N>& B) {
		std::array<double, N> Cvals;
		for (int i = 0; i < N; i++) {
			Cvals = A[i] - B[i];
		}
		return Vector<N>(Cvals);
	}

	template<std::uint64_t N>
	inline Vector<N> operator*(const Vector<N>& A, const Vector<N>& B) {
		std::array<double, N> Cvals;
		for (int i = 0; i < N; i++) {
			Cvals = A[i] * B[i];
		}
		return Vector<N>(Cvals);
	}

	template<std::uint64_t N>
	inline Vector<N> operator*(double lambda, const Vector<N>& A) {
		std::array<double, N> Cvals;
		for (int i = 0; i < N; i++) {
			Cvals = A[i] * lambda;
		}
		return Vector<N>(Cvals);
	}

	template<std::uint64_t N>
	inline Vector<N> operator*(const Vector<N>& A, double lambda) {
		return A * lambda;
	}

	template<std::uint64_t N>
	inline Vector<N> dot(const Vector<N>& A, const Vector<N>& B) {
		double result;
		for (int i = 0; i < N; i++) {
			result += A[i] * B[i];
		}
		return result;
	}

	inline Vector<3> cross(const Vector<3>& u, const Vector<3>& v) {
		return Vector<3>(u.Y() * v.Z() - u.Z() * v.Y(),
			u.Z() * v.X() - u.X() * v.Z(),
			u.X() * v.Y() - u.Y() * v.X());
	}

}