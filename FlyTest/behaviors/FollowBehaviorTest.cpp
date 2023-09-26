#include "../pch.h"
#include <objects/bird.h>
#include <objects/Object.h>
#include <behaviors/FollowBehavior.h>
#include "../Mocks/BehaviorTargetMock.h"

TEST(FollowBehaviorTest, SetOffsetWhenNorth) {
	// Arrange
	BehaviorTargetMock subject = BehaviorTargetMock();
	Object target = Object(glm::vec3(10, 0, 10), glm::vec3(0, 0, 1));
	FollowBehavior behavior = FollowBehavior();
	behavior.setOffset(glm::vec3(-5, 0, -5));
	behavior.setBehaviorTarget(&subject);
	behavior.setFollowTarget(&target);

	// Act
	behavior.think(0, 0);

	// Assert
	glm::vec3 destination = subject.getDestination();
	EXPECT_EQ(glm::vec3(5, 0, 5), destination);
}

TEST(FollowBehaviorTest, SetOffsetWhenSouth) {
	// Arrange
	BehaviorTargetMock subject = BehaviorTargetMock();
	Object target = Object(glm::vec3(10, 0, 10), glm::vec3(0, 0, -1));
	FollowBehavior behavior = FollowBehavior();
	behavior.setOffset(glm::vec3(-5, 0, -5));
	behavior.setBehaviorTarget(&subject);
	behavior.setFollowTarget(&target);

	// Act
	behavior.think(0, 0);

	// Assert
	glm::vec3 destination = subject.getDestination();
	EXPECT_EQ(glm::vec3(15, 0, 15), destination);
}

TEST(FollowBehaviorTest, SetOffsetWhenDiagonal) {
	// Arrange
	BehaviorTargetMock subject = BehaviorTargetMock();
	Object target = Object(glm::vec3(10, 0, 10), glm::vec3(0.7071f, 0, 0.7071f));
	FollowBehavior behavior = FollowBehavior();
	behavior.setOffset(glm::vec3(-5, 0, -5));
	behavior.setBehaviorTarget(&subject);
	behavior.setFollowTarget(&target);

	// Act
	behavior.think(0, 0);

	// Assert
	glm::vec3 destination = subject.getDestination();
	ASSERT_NEAR(2.929f, destination.x, 0.0001f);
	ASSERT_NEAR(10, destination.z, 0.0001f);
}