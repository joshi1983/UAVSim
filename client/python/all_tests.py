import glob
import unittest

testSuite = unittest.TestSuite()
test_file_strings = glob.glob('unit_tests/*_test.py')
module_strings = [str[0:-3].replace('\\', '.') for str in test_file_strings]
[__import__(str) for str in module_strings]
suites = []
for module_string in module_strings:
	suites.append(unittest.TestLoader().loadTestsFromName(module_string))

[testSuite.addTest(suite) for suite in suites]

result = unittest.TestResult()
testSuite.run(result)
print result

if __name__ == "__main__":
     unittest.main()