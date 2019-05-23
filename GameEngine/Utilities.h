#pragma once
class Utilities
{
public:

	//checks if baseType is base of derivedType, as well as check if derivedType and baseType are not the same
	template<typename derivedType, typename baseType>
	static void checkValidityOfType()
	{
		const bool T_DerivedFromComponent = std::is_base_of<baseType, derivedType>::value;
		const bool T_is_Component = std::is_same<derivedType, baseType>::value;
		static_assert(T_DerivedFromComponent, "derivedType should be derived from baseType as: '<derivedType, baseType>");
		static_assert(!T_is_Component, "function template parameters cannot be same, they have to be as: '<derivedType, baseType>");
	}
};
