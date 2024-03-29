/**
 * Test for a regression of Bug 437556: mailnews crashes while importing an 
 * address book if a field map is required but not set.
 */
function run_test()
{
  var file = do_get_file("resources/basic_addressbook.csv");
  var errorStr = Cc["@mozilla.org/supports-string;1"]
                  .createInstance(Ci.nsISupportsString);
  // get the Address Book text import interface and make sure it succeeded
  var helper = new AbImportHelper(file, "CSV");
  var abInterface = helper.getInterface("addressbook", ".csv");
  do_check_neq(abInterface, null);
  // prepare to start the import
  abInterface.SetData("addressLocation", file);
  do_check_true(abInterface.WantsProgress());
  // start the import
  // BeginImport should return false and log an error if the fieldMap isn't set
  do_check_false(abInterface.BeginImport(null, errorStr, false));
  do_check_neq(errorStr, "");
}
