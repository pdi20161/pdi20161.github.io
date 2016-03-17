std::array<int,4> foo {0,1,2,3};

// obtain a time-based seed:
unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

shuffle (foo.begin(), foo.end(), std::default_random_engine(seed));

std::cout << "shuffled elements:";
for (int& x: foo){
  aleint[i] = x;
  i++;
}
