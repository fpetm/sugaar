#pragma once
#include <cstdint>
#include <array>
#include <random>

namespace sugaar {
	template <std::uint64_t N>
	class Vector {
	public:
		Vector<N>() : e() {}
		Vector<N>(std::array<double, N> vals) : e(vals) {}

		template<std::uint64_t N = 2> Vector(double x, double y) : e({ x,y }) {}
		template<std::uint64_t N = 3> Vector(double x, double y, double z) : e({ x,y,z }) {}
		template<std::uint64_t N = 4> Vector(double x, double y, double z, double w) : e({ x,y,z,w }) {}
		template<std::uint64_t N = 4> Vector(Vector<3> v, double w) : e({ v.X(), v.Y(), v.Z(), w}) {}


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
			return dot(*this, *this);
		}

		inline static Vector<N> random() {
			Vector<N> result;
			for (int i = 0; i < N; i++) {
				result[i] = random();
			}
			return result;
		}

		inline static Vector<N> random(double min, double max) {
			Vector<N> result;
			for (int i = 0; i < N; i++) {
				result[i] = random_double(min, max);
			}
			return result;
		}

		inline static Vector<N> random_in_unit_sphere() {
			while (true) {
				auto p = Vector<N>::random(-1, 1);
				if (p.length_squared() >= 1) continue;
				return p;
			}
		}

		inline static Vector<N> random_unit_vector() {
			return unit_vector(Vector<N>::random_in_unit_sphere());
		}

		bool near_zero() const {
			const auto s = 1e-8;
			for (int i = 0; i < N; i++) {
				if (abs(e[i]) >= s) return false;
			}
			return true;
		}
	private:
		std::array<double, N> e;
	};

	template<std::uint64_t N>
	inline std::ostream& operator<<(std::ostream& out, const Vector<N>& v) {
		for (int i = 0; i < N; i++) {
			out << v[i] << " ";
		}
		return out;
	}
	
	template<std::uint64_t N = 3>
	inline Vector<N> operator+(const Vector<3>& A, const Vector<3>& B) {
		return Vec3(A.X() + B.X(), A.Y() + B.Y(), A.Z() + B.Z());
	}

	template<std::uint64_t N>
	inline Vector<N> operator+(const Vector<N>& A, const Vector<N>& B) {
		std::array<double, N> Cvals;
		for (int i = 0; i < N; i++) {
			Cvals[i] = A[i] + B[i];
		}
		return Vector<N>(Cvals);
	}
	
	template<std::uint64_t N = 3>
	inline Vector<N> operator-(const Vector<3>& A, const Vector<3>& B) {
		return Vec3(A.X() - B.X(), A.Y() - B.Y(), A.Z() - B.Z());
	}

	template<std::uint64_t N>
	inline Vector<N> operator-(const Vector<N>& A, const Vector<N>& B) {
		std::array<double, N> Cvals;
		for (int i = 0; i < N; i++) {
			Cvals[i] = A[i] - B[i];
		}
		return Vector<N>(Cvals);
	}

	template<std::uint64_t N>
	inline Vector<N> operator*(const Vector<N>& A, const Vector<N>& B) {
		std::array<double, N> Cvals;
		for (int i = 0; i < N; i++) {
			Cvals[i] = A[i] * B[i];
		}
		return Vector<N>(Cvals);
	}
	
	template<std::uint64_t N = 3>
	inline Vector<3> operator*(double lambda, const Vector<3>& A) {
		return Vec3(lambda * A.X(), lambda * A.Y(), lambda * A.Z());
	}

	template<std::uint64_t N>
	inline Vector<N> operator*(double lambda, const Vector<N>& A) {
		std::array<double, N> Cvals;
		for (int i = 0; i < N; i++) {
			Cvals[i] = A[i] * lambda;
		}
		return Vector<N>(Cvals);
	}

	template<std::uint64_t N>
	inline Vector<N> operator*(const Vector<N>& A, double lambda) {
		return lambda * A;
	}

	template<std::uint64_t N>
	inline Vector<N> operator/(const Vector<N>& A, double lambda) {
		return A * (1/lambda);
	}
	
	template<std::uint64_t N = 3>
	inline double dot(const Vector<3>& A, const Vector<3>& B) {
		return (A.X() * B.X()) + (A.Y() * B.Y()) + (A.Z() * B.Z());
	}

	template<std::uint64_t N>
	inline double dot(const Vector<N>& A, const Vector<N>& B) {
		double result = 0.0;
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

	template<std::uint64_t N>
	inline Vector<N> unit_vector(const Vector<N>& A) {
		return A / A.length();
	}

	template<std::uint64_t N>
	inline Vector<N> reflect(const Vector<N>& v, const Vector<N>& n) {
		return v - 2 * dot(v, n) * n;
	}

	typedef Vector<2> Vec2;
	typedef Vector<3> Vec3;
	typedef Vector<4> Vec4;

	// returns a random number in the interval [0,1[
	inline double random_double() {
		static std::uniform_real_distribution<double> distribution(0.0, 1.0);
		static std::mt19937 generator;
		return distribution(generator);
	}

	inline double random_double(double min, double max) {
		return min + (max - min) * random_double();
	}

	inline double clamp(double x, double min, double max) {
		if (x < min) return min;
		if (x > max) return max;
		return x;
	}


}