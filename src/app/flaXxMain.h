#ifndef FLAXX_MAIN_H
#define FLAXX_MAIN_H

namespace flaXx
{

class FlaxxMain
{
	public:
		int main (int argc, char *argv[]);

		static tr1::shared_ptr<FlaxxMain> instance();

	private:
		// Privat kostruktor eftersom klassen är
		// singleton.
		FlaxxMain();

		CommandLineParser cmdParser;
		tr1::shared_ptr<Render> render;

		// Singletoninstansen
		static tr1::shared_ptr<FlaxxMain> instance;
};

} // namespace flaXx
#endif
