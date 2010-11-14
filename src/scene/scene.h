#ifndef SCENE_H
#define SCENE_H


namespace flaXx
{

/** Klass för att representera en
 * scen. */
class Scene
{
  public:
	/** Default-konstruktor som skapar vår
	 * exempelscen. */
	Scene();


	/** Metod som skapar en ray
	 * och skjuter den in i scenen. Den går
	 * sedan igenom alla objekt och kontrollerar
	 * intersection. Returnerar sedan punkten. */
	Vector3f shootRay(Ray, std::tr1::shared_ptr<Object>);

  private:

	Camera camera;
	std::list<Light> lights;
	std::list<Object> objects;

};

} // end namespace flaXx
#endif // SCENE_H
