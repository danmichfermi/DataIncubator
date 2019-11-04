import pandas as pd

policy_df = pd.read_csv('openFEMA_claims20190630.csv', engine='python')
claims_df = pd.read_csv('splitpolicies.part00', engine='python')


policyhead=policy_df.head(10)
claimhead=claims_df.head(10)

print(policyhead)

outclaimhead.close()


policycheck=policy_df.describe()
claimcheck=policy_df.descripe()

print(policycheck)
print(claimcheck)

outclaimdescribe.close()
