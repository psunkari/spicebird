#include "nsIVariant.h"
#include "nsComponentManagerUtils.h"
#include "nsCOMPtr.h"
#include "nsStringGlue.h"

#include "telepathy-glib/gtypes.h"

nsresult GValueToVariant(const GValue *aGValue, nsIVariant **aVariant)
{
  nsCOMPtr<nsIWritableVariant> writable = do_CreateInstance(NS_VARIANT_CONTRACTID);
  int type = G_VALUE_TYPE(aGValue);

  switch(type) {
    case G_TYPE_UCHAR:
      writable->SetAsUint8(g_value_get_uchar(aGValue));
      break;

    case G_TYPE_BOOLEAN:
      writable->SetAsBool(g_value_get_boolean(aGValue));
      break;

    case G_TYPE_INT:
      writable->SetAsInt32(g_value_get_int(aGValue));
      break;

    case G_TYPE_UINT:
      writable->SetAsUint32(g_value_get_uint(aGValue));
      break;

    case G_TYPE_INT64:
      writable->SetAsInt64(g_value_get_int64(aGValue));
      break;

    case G_TYPE_UINT64:
      writable->SetAsUint64(g_value_get_uint64(aGValue));
      break;

    case G_TYPE_DOUBLE:
      writable->SetAsDouble(g_value_get_double(aGValue));
      break;

    case G_TYPE_STRING:
      writable->SetAsString(g_value_get_string(aGValue));
      break;

    default:
#ifdef _DEBUG
      g_print("Oops! Unhandled type in GValueToVariant!\n");
#endif
      *aVariant = NULL;
      return NS_ERROR_NOT_IMPLEMENTED;
  }

  NS_ADDREF(*aVariant = writable);
  return NS_OK;
}

GValue *VariantToGValue(nsIVariant *aVariant)
{
  GValue *value = g_new0(GValue, 1);
  nsString strValue;
  nsresult rv;

  PRUint16 type;
  aVariant->GetDataType(&type);

  switch (type) {
    case nsIDataType::VTYPE_CHAR_STR:
    case nsIDataType::VTYPE_UTF8STRING:
    case nsIDataType::VTYPE_CSTRING:
    case nsIDataType::VTYPE_ASTRING:
    case nsIDataType::VTYPE_STRING_SIZE_IS:
    case nsIDataType::VTYPE_WSTRING_SIZE_IS:
      rv = aVariant->GetAsAString(strValue);
      if (NS_FAILED(rv))
        goto ValueError;

      g_value_init(value, G_TYPE_STRING);
      g_value_set_string(value, NS_ConvertUTF16toUTF8(strValue).get());
      break;

    case nsIDataType::VTYPE_BOOL:
      PRBool boolValue;
      rv = aVariant->GetAsBool(&boolValue);
      if (NS_FAILED(rv))
        goto ValueError;

      g_value_init(value, G_TYPE_BOOLEAN);
      g_value_set_boolean(value, boolValue);
      break;

    case nsIDataType::VTYPE_UINT32:
      PRUint32 uint32Value;
      rv = aVariant->GetAsUint32(&uint32Value);
      if (NS_FAILED(rv))
        goto ValueError;

      g_value_init(value, G_TYPE_UINT);
      g_value_set_uint(value, uint32Value);
      break;

    case nsIDataType::VTYPE_INT32:
      PRInt32 int32Value;
      rv = aVariant->GetAsInt32(&int32Value);
      if (NS_FAILED(rv))
        goto ValueError;

      g_value_init(value, G_TYPE_INT);
      g_value_set_int(value, int32Value);
      break;

    case nsIDataType::VTYPE_UINT64:
      PRUint64 uint64Value;
      rv = aVariant->GetAsUint64(&uint64Value);
      if (NS_FAILED(rv))
        goto ValueError;

      g_value_init(value, G_TYPE_UINT64);
      g_value_set_uint64(value, uint64Value);
      break;

    case nsIDataType::VTYPE_INT64:
      PRInt64 int64Value;
      rv = aVariant->GetAsInt64(&int64Value);
      if (NS_FAILED(rv))
        goto ValueError;

      g_value_init(value, G_TYPE_INT64);
      g_value_set_int64(value, int64Value);
      break;

    case nsIDataType::VTYPE_DOUBLE:
      double doubleValue;
      rv = aVariant->GetAsDouble(&doubleValue);
      if (NS_FAILED(rv))
        goto ValueError;

      g_value_init(value, G_TYPE_DOUBLE);
      g_value_set_double(value, doubleValue);
      break;

    default:
#ifdef _DEBUG
      g_print("Oops! Unhandled type in VariantToGValue: %d\n", type);
#endif
      break;
  }

  return value;

ValueError:
  g_free(value);
  return NULL;
}

GValue *VariantToGValueWithSignature(nsIVariant *aVariant, char *aSignature)
{
  GValue *value = g_new0(GValue, 1);
  nsCString cStrValue;
  nsresult rv;

  switch (aSignature[0]) {

    case 's':
      rv = aVariant->GetAsACString(cStrValue);
      if (NS_FAILED(rv))
        goto ValueError;

      g_value_init(value, G_TYPE_STRING);
      g_value_set_string(value, cStrValue.get());
      break;

    case 'b':
      PRBool boolValue;
      rv = aVariant->GetAsBool(&boolValue);
      if (NS_FAILED(rv))
        goto ValueError;

      g_value_init(value, G_TYPE_BOOLEAN);
      g_value_set_boolean(value, boolValue);
      break;

    case 'q':
    case 'u':
      PRUint32 uint32Value;
      rv = aVariant->GetAsUint32(&uint32Value);
      if (NS_FAILED(rv))
        goto ValueError;

      g_value_init(value, G_TYPE_UINT);
      g_value_set_uint(value, uint32Value);
      break;

    case 'n':
    case 'i':
      PRInt32 int32Value;
      rv = aVariant->GetAsInt32(&int32Value);
      if (NS_FAILED(rv))
        goto ValueError;

      g_value_init(value, G_TYPE_INT);
      g_value_set_int(value, int32Value);
      break;

    case 't':
      PRUint64 uint64Value;
      rv = aVariant->GetAsUint64(&uint64Value);
      if (NS_FAILED(rv))
        goto ValueError;

      g_value_init(value, G_TYPE_UINT64);
      g_value_set_uint64(value, uint64Value);
      break;

    case 'x':
      PRInt64 int64Value;
      rv = aVariant->GetAsInt64(&int64Value);
      if (NS_FAILED(rv))
        goto ValueError;

      g_value_init(value, G_TYPE_INT64);
      g_value_set_int64(value, int64Value);
      break;

    case 'd':
      double doubleValue;
      rv = aVariant->GetAsDouble(&doubleValue);
      if (NS_FAILED(rv))
        goto ValueError;

      g_value_init(value, G_TYPE_DOUBLE);
      g_value_set_double(value, doubleValue);
      break;

    default:
#ifdef _DEBUG
      g_print("Oops! Unknown Parameter Type!\n");
#endif
      break;
  }

  return value;

ValueError:
  g_free(value);
  return NULL;
}
