#include <iostream>
#include <string>
#include <cstdint>
#include <vector>
#include <algorithm>
#include <random>

const std::string target = "???????*?*???#";
const int bw = 10000;
const int limit = 10000000;
const bool debug = false;

struct Program {
  unsigned char a = 0, w = 0, h = '#', q = '?';
  long long int p = 0, y = 0;
  unsigned int g = 89404137;
  std::string b = "", code = "";
  float rank = 0.0f;
};

inline void rank(struct Program& program, const std::string target, std::mt19937& engine, std::uniform_real_distribution<float>& distribution) {
  program.rank = 0.0f;
  for (int i = 0; i < (int)std::min(target.length(), program.b.length()); i++)
    program.rank += (target[i] == program.b[i] ? 1000.0f : -100.0f);
  program.rank -= 0.05f * (float)program.code.length();
  program.rank += ((program.g >> 16) & 0xFF == 23) * 1000.0f;
  program.rank += (program.p % 2 == 0) * 1000.0f;
  program.rank += distribution(engine);
}

bool step(struct Program& program, const std::string target) {
  program.g = program.g * 1664525 + 1013904223 + program.a + program.w + program.h + program.q + program.p + program.code.back();
  switch(((((program.code.back()^program.q) + ((program.code.length() - 1) % 3) + (program.g >> 24)) % 3) + 3) % 3) {
    case 0:
      program.a += 3;
      program.w += 7;
      program.p -= 13;
      program.q -= 43;
      program.g ^= 0xCAFEBABE;
      break;
    case 1:
      program.a -= 2;
      program.w -= 5;
      program.q += 67;
      program.p += 17;
      program.g += program.a ^ program.w;
      break;
    case 2:
      program.b += (~(((program.a | program.w) & program.h) ^ program.q ^ (program.g & 0xFF)));
      if(std::string("*#?").find(program.b.back()) == std::string::npos)
        program.g=0xDEADBEEF;
      if(program.b.length() > target.length() || program.b.back() != target[program.b.length() - 1])
        return false;
      break;
  }
  return true;
}

bool constraints(const struct Program program) {
  return ((char)((program.g >> 16) & 0xFF) == 23) && program.p % 2 == 0;
}

void search(const std::string target, std::vector<struct Program>& beam) {
  std::mt19937 engine(std::random_device{}());
  std::uniform_real_distribution<float> distribution(-0.1f, 0.1f);
  std::string instructions;
  for (char i = 32; i < 126; i++)
    instructions += i;
  
  for (int i = 0; i < limit; i++) {
  	std::vector<struct Program> candidates;
  	candidates.reserve(beam.size() * 94);

  	for (auto& program : beam) {
  	  for (char instruction : instructions) {
  	  	struct Program next = program;
        next.code += instruction;
  	  	if (step(next, target)) {
  	  	  rank(next, target, engine, distribution);
          if ((next.b.length() == target.length()) && constraints(next)) {
            std::cout << "Solution: " << next.code << std::endl;
            return;
          }
  	  	  candidates.push_back(std::move(next));
  	  	}
  	  }
  	}

  	std::partial_sort(candidates.begin(), candidates.begin() + std::min(bw, (int)candidates.size()), candidates.end(), [](auto& a, auto& b) { return a.rank > b.rank; });
  	candidates.resize(bw);
  	beam = std::move(candidates);
  	if (debug || i % 1000 == 0)
  	  std::cout << "[Iteration " << i << '/' << limit << ']' << " Best solution: " << beam[0].code << " Progress: " << beam[0].b.length() << '/' << target.length() << std::endl;
  }
}

int main() {
  std::vector<struct Program> beam = {{}};
  search(target, beam);
  return 0;
}
