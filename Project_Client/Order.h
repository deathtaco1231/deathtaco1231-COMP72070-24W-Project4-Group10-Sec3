#include "AllHeaders.h"
#include "Package.h"
#include "Date.h"
#include "Courier.h"
class Completed {
protected:
	Package p;
	date completedOn;
	Courier deliveredBy;
public:
	Completed();
	Completed(Package&, date&, Courier&);
	void setPackage(Package&);
	void setDate(date&);
	void setCourier(Courier&);
	Package getPackage();
	date getDate();
	Courier getCourier();
};