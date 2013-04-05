#ifndef _CS_TELEPATHY_UTILS_H_
#define _CS_TELEPATHY_UTILS_H_

#include "nsIVariant.h"

nsresult GValueToVariant(const GValue *gval, nsIVariant **variant);
GValue *VariantToGValue(nsIVariant *var);
GValue *VariantToGValueWithSignature(nsIVariant *aVariant, char *aSignature);

#endif
