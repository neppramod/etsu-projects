Feature: PersonalGPATrackerAddNewCourse
	In order to calculate overall GPA
	As a CS student
	I want to add a course

Background:
	Given I navigate to the Course Add page

@Normal_Flow
Scenario: Add a course
	Given I have entered CSCI3110 as the Code
		And I have entered Advanced Web Design and Development as the Title
		And I have selected 3 as the Credit Hours
		And I have selected B- as the Letter Grade
	When I issue the Add Course command
	Then the page should go to home page and course added to list
