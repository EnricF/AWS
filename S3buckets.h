#pragma once
// Amazone Web Services!
#include <aws/core/Aws.h>

void ListBucket();
void DeleteBucket();
bool create_bucket(const Aws::String& bucket_name, const Aws::S3::Model::BucketLocationConstraint& region = Aws::S3::Model::BucketLocationConstraint::EU);

